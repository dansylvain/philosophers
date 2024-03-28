/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filo_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:44:04 by dan               #+#    #+#             */
/*   Updated: 2024/03/28 02:13:09 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filo_routine.h"

/**========================================================================
 *                           filo_rtn 
 *========================================================================**/
void	*filo_rtn(void *arg)
{
	t_filo			*filo;
	long int		time_now;
	struct timeval	now;

	filo = (t_filo *)arg;
	xpress_mssg(filo, thinking);
	if (filo->id % 2 == 0)
		usleep (1000);
	get_time_now(&time_now);
	while (time_now < filo->meal_time + filo->data->tt_die)
	{
		if (check_stop_condition(filo) == 0)
			return (NULL);
		if (filo->meals_taken == filo->max_meals)
			return (unlock_forks(filo), NULL);
		get_forks(filo);
		if (eat_and_sleep(filo) == 0)
			return (unlock_forks(filo), NULL);
		gettimeofday(&now, NULL);
		time_now = time_to_ms(now);
	}
	check_death_condition(filo);
	unlock_forks(filo);
	return (NULL);
}

/**========================================================================
 *                           check_stop_condition	
 *========================================================================**/
int	check_stop_condition(t_filo *filo)
{
	pthread_mutex_lock(&filo->data->stop_mtx);
	if (filo->data->stop == true)
	{
		pthread_mutex_unlock(&filo->data->stop_mtx);
		unlock_forks(filo);
		return (0);
	}
	pthread_mutex_unlock(&filo->data->stop_mtx);
	return (1);
}

/**========================================================================
 *                           get_forks 
 *========================================================================**/
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

/**========================================================================
 *                           unlock_forks
 *========================================================================**/
void	unlock_forks(t_filo *filo)
{
	if (filo->lfork_taken)
		pthread_mutex_unlock(&filo->data->fork[filo->id]);
	if (filo->rfork_taken)
		pthread_mutex_unlock(&filo->data->fork
		[(filo->id + 1) % filo->data->fil_nbr]);
}

/**========================================================================
 *                           eat_and_sleep 
 *========================================================================**/
int	eat_and_sleep(t_filo *filo)
{
	if (filo->data->fil_nbr > 1 && filo->rfork_taken == true
		&& filo->lfork_taken == true)
	{
		pthread_mutex_lock(&filo->data->stop_mtx);
		if (time_is_up(filo) || filo->data->stop == true)
			return (pthread_mutex_unlock(&filo->data->stop_mtx), 0);
		pthread_mutex_unlock(&filo->data->stop_mtx);
		xpress_mssg(filo, eating);
		get_time_now(&filo->meal_time);
		usleep(filo->data->tt_eat * 1000);
		pthread_mutex_lock(&filo->data->stop_mtx);
		if (filo->data->stop == true)
			return (pthread_mutex_unlock(&filo->data->stop_mtx), 0);
		pthread_mutex_unlock(&filo->data->stop_mtx);
		unlock_forks(filo);
		filo->lfork_taken = false;
		filo->rfork_taken = false;
		filo->meals_taken++;
		xpress_mssg(filo, sleeping);
		usleep(filo->data->tt_sleep * 1000);
		xpress_mssg(filo, thinking);
	}
	return (1);
}
