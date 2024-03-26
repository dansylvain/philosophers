/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filo_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:44:04 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 12:49:11 by dan              ###   ########.fr       */
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
int		time_is_up(t_filo *filo);
void	check_death_condition(t_filo *filo);
void	get_forks(t_filo *filo);
int	eat_and_sleep(t_filo *filo);

void	*filo_rtn(void *arg)
{
	t_filo			*filo;
	long int		time_now;
	struct timeval	now;

	filo = (t_filo *)arg;
	xpress_mssg(filo, thinking);
	if (filo->id % 2 == 0)
		usleep (filo->data->tt_eat / 2 * 1000);
	time_now = time_to_ms(now);
	while (time_now < filo->meal_time + filo->data->tt_die)
	{
		if (filo->data->stop == true)
			return (NULL);
		if (filo->meals_taken == filo->max_meals)
			return (NULL);
		get_forks(filo);
		if (eat_and_sleep(filo) == 0)
			return (NULL);
		gettimeofday(&now, NULL);
		time_now = time_to_ms(now);
	}
	check_death_condition(filo);
	return (NULL);
}

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

int	eat_and_sleep(t_filo *filo)
{
	long int		time_now;
	struct timeval	now;

	if (filo->data->fil_nbr > 1 && filo->rfork_taken == true
		&& filo->lfork_taken == true)
	{
		if (time_is_up(filo) || filo->data->stop == true)
			return (0);
		xpress_mssg(filo, eating);
		get_time_now(&filo->meal_time);
		usleep(filo->data->tt_eat * 1000);
		if (filo->data->stop == true)
			return (0);
		pthread_mutex_unlock(&filo->data->fork[filo->id]);
		pthread_mutex_unlock(&filo->data->fork
		[(filo->id + 1) % filo->data->fil_nbr]);
		filo->lfork_taken = false;
		filo->rfork_taken = false;
		filo->meals_taken++;
		xpress_mssg(filo, sleeping);
		usleep(filo->data->tt_sleep * 1000);
		xpress_mssg(filo, thinking);
	}
	return (1);
}

