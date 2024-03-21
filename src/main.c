/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/21 12:00:41 by dan              ###   ########.fr       */
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

t_filo *eat_and_sleep(t_filo *filo)
{
	if (filo->id == 0)
	{
		// printf("filo->meal_time: %li\n", filo->meal_time);
		
		get_time_now(&filo->meal_time);
		xpress_mssg(filo, eating);
		usleep(filo->data->tt_eat);
		xpress_mssg(filo, sleeping);
		usleep(filo->data->tt_sleep);
	}
	return (filo);
}

void	*filo_rtn(void *arg)
{
	t_filo			*filo;
	long int		time_now;

	filo = (t_filo *)arg;
	xpress_mssg(filo, got_born);
	while (time_now < filo->meal_time + filo->data->tt_die)
	{
		
		eat_and_sleep(filo);
		get_time_now(&time_now);
		// printf("time_now %li < filo->meal_time %li + filo->data->tt_die %i\n", time_now, filo->meal_time, filo->data->tt_die);
	}
	xpress_mssg(filo, dead);
	return (NULL);
}

void	*coor_rtn(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (i < 3)
	{
		sleep(1);
		pthread_mutex_lock(&data->print_mtx);
		printf("%i: I'm watching you...\n", data->fil_nbr);
		pthread_mutex_unlock(&data->print_mtx);
		i++;
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
	pthread_mutex_destroy(&data->print_mtx);
	free_data(data);
	return (0);
}
