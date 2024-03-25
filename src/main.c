/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/25 09:14:26 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <pthread.h>
# include <sys/time.h>
#include <unistd.h>

int		check_input(int argc, char **argv);
void	free_data(t_Data *data);
void	display_error(char *str);
int		create_and_initialize_data(t_Data **data, char **argv);
t_Data	*run_threads(t_Data *data);
void	xpress_mssg(t_filo *filo, mssg mssg);
long	time_to_ms(struct timeval time_struct);
t_Data *run_threads(t_Data *data);
void	get_time_now(long int	*time_now);


void	*filo_rtn(void *arg)
{
	t_filo 		*filo;
	long int	time_now;
	struct timeval now;
	pthread_mutex_t *lfork;
	pthread_mutex_t *rfork;
	
	
	filo = (t_filo *)arg;
	lfork = &filo->data->fork[filo->id];
	rfork = &filo->data->fork[(filo->id + 1) % filo->data->fil_nbr];
	xpress_mssg(filo, thinking);
	if (filo->id % 2 == 0)
		usleep (filo->data->tt_eat / 2 * 1000);
	while (time_now < filo->meal_time * 1000 + filo->data->tt_die * 1000)
	{
		pthread_mutex_lock(lfork);
		xpress_mssg(filo, take_fork);
		pthread_mutex_trylock(rfork);
		xpress_mssg(filo, take_fork);
		xpress_mssg(filo, eating);
		get_time_now(&filo->meal_time);
		usleep(filo->data->tt_eat * 1000);
		pthread_mutex_unlock(lfork);
		pthread_mutex_unlock(rfork);
		xpress_mssg(filo, sleeping);
		usleep(filo->data->tt_sleep * 1000);
		xpress_mssg(filo, thinking);
		gettimeofday(&now, NULL);
		time_now = time_to_ms(now);
	}
	xpress_mssg(filo, dead);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_Data	*data;
	int		i;
	
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_and_initialize_data(&data, argv) == 0)
		return (free_data(data), display_error("Error\n"), 2);
		
	data = run_threads(data);
	if (data == NULL)
		return (free_data(data), display_error("Error\n"), 3);
	
	pthread_mutex_destroy(&data->print_mtx);
	free_data(data);
	return (0);
}


