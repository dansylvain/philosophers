/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/21 20:57:33 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

int		check_input(int argc, char **argv);
void	free_data(t_data *data);
void	display_error(char *str);
int		create_and_initialize_data(t_data **data, char **argv);
t_data	*run_threads(t_data *data);
void	xpress_mssg(t_filo *filo, t_mssg mssg);
long	time_to_ms(struct timeval time_struct);
t_data	*run_threads(t_data *data);
void	get_time_now(long int	*time_now);
void	destroy_mutexes(t_data *data);
/**========================================================================
 *                             DON'T FORGET!!!
 *! beware of units!!!  
 *! time is converted to ms for input and display purpose 
 *! but funcs handle microseconds!!!  
 *  
 *========================================================================**/
t_filo	*eat_and_sleep(t_filo *filo)
{
	pthread_mutex_lock(&filo->can_eat_mtx);
	filo->can_eat = false;
	pthread_mutex_unlock(&filo->can_eat_mtx);
	get_time_now(&filo->meal_time);	
	xpress_mssg(filo, eating);
	usleep(filo->data->tt_eat * 1000);
	xpress_mssg(filo, sleeping);
	usleep(filo->data->tt_sleep * 1000);
	return (filo);
}

int	filo_can_eat(t_filo *filo)
{
	int	yes_or_no;
	
	yes_or_no = 0;
	pthread_mutex_lock(&filo->can_eat_mtx);
	// printf("filo_can_eat % i\n", filo->id);
	if (filo->can_eat == true)
		yes_or_no = 1;
	pthread_mutex_unlock(&filo->can_eat_mtx);
	// printf("yes_or_no: %i\n", yes_or_no);
	return (yes_or_no);
}

void	*filo_rtn(void *arg)
{
	t_filo			*filo;
	long int		time_now;

	time_now = 0;
	filo = (t_filo *)arg;
	xpress_mssg(filo, got_born);
	while (time_now < filo->meal_time + filo->data->tt_die)
	{
		usleep(100);
		if (filo_can_eat(filo))
			filo = eat_and_sleep(filo);
		get_time_now(&time_now);
	}
	xpress_mssg(filo, dead);
	return (NULL);
}

void	*coor_rtn(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->filo[0].can_eat_mtx);
		data->filo[0].can_eat = true;
		// printf("data->filo[0].can_eat: %i\n", data->filo[0].can_eat);
		pthread_mutex_unlock(&data->filo[0].can_eat_mtx);

		// pthread_mutex_lock(&data->print_mtx);
		// printf("%i: I'm watching you...\n", data->fil_nbr);
		// pthread_mutex_unlock(&data->print_mtx);
		// i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_and_initialize_data(&data, argv) == 0)
		return (free_data(data), display_error("Error\n"), 2);
	printf("welcome to the jungle\n");
	data = run_threads(data);
	if (data == NULL)
		return (free_data(data), display_error("Error\n"), 3);
	destroy_mutexes(data);
	free_data(data);
	return (0);
}
