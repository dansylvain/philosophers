/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/25 16:56:59 by dan              ###   ########.fr       */
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

void	get_forks(t_filo *filo)
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;

	lfork = &filo->data->fork[filo->id];
	rfork = NULL;
	if (filo->data->fil_nbr > 1)
		rfork = &filo->data->fork[(filo->id + 1) % filo->data->fil_nbr];
	if (pthread_mutex_trylock(lfork) == 0)
	{
		filo->lfork_taken = true;
		xpress_mssg(filo, take_fork);
	}
	if (rfork && pthread_mutex_trylock(rfork) == 0)
	{
		filo->rfork_taken = true;
		xpress_mssg(filo, take_fork);
	}
}

void	eat_and_sleep(t_filo *filo)
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;

	lfork = &filo->data->fork[filo->id];
	rfork = NULL;
	if (filo->data->fil_nbr > 1)
		rfork = &filo->data->fork[(filo->id + 1) % filo->data->fil_nbr];
	if (filo->data->fil_nbr > 1 && filo->rfork_taken == true
		&& filo->lfork_taken == true)
	{
		xpress_mssg(filo, eating);
		get_time_now(&filo->meal_time);
		usleep(filo->data->tt_eat * 1000);
		pthread_mutex_unlock(lfork);
		pthread_mutex_unlock(rfork);
		filo->lfork_taken = false;
		filo->rfork_taken = false;
		filo->meals_taken++;
		xpress_mssg(filo, sleeping);
		usleep(filo->data->tt_sleep * 1000);
		xpress_mssg(filo, thinking);
	}
}

void	*filo_rtn(void *arg)
{
	t_filo			*filo;
	long int		time_now;
	struct timeval	now;

	filo = (t_filo *)arg;
	xpress_mssg(filo, thinking);
	if (filo->id % 2 == 0)
		usleep (filo->data->tt_eat / 2 * 1000);
	while (time_now < filo->meal_time + filo->data->tt_die)
	{
		if (filo->meals_taken == filo->max_meals)
			return (NULL);
		get_forks(filo);
		eat_and_sleep(filo);
		gettimeofday(&now, NULL);
		time_now = time_to_ms(now);
	}
	xpress_mssg(filo, dead);
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
	data = run_threads(data);
	if (data == NULL)
		return (free_data(data), display_error("Error\n"), 3);
	pthread_mutex_destroy(&data->print_mtx);
	free_data(data);
	return (0);
}

t_data	*run_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->fil_nbr)
	{
		data->filo[i].id = i;
		if (pthread_create(&data->filo[i].filo, NULL,
				filo_rtn, &data->filo[i]) != 0)
			return (NULL);
		i++;
	}
	i = 0;
	while (i < data->fil_nbr)
	{
		if (pthread_join(data->filo[i].filo, NULL) != 0)
			return (NULL);
		i++;
	}
	return (data);
}
