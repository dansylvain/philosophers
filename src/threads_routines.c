/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:39:03 by dan               #+#    #+#             */
/*   Updated: 2024/03/24 07:49:38 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

int		one_filo_died(t_data *data);
void	xpress_mssg(t_filo *filo, t_mssg mssg);
t_data	*run_threads(t_data *data);
void	get_time_now(long int	*time_now);
void	filo_dies(t_filo *filo);
void	display_auth_tab(t_data *data);
t_filo	*add_id_to_auth_lst(t_filo *filo);
int		all_filos_are_out(t_data *data);

/**========================================================================
 *                             DON'T FORGET!!!
 *! beware of units!!!  
 *! time is converted to ms for input and display purpose 
 *! but funcs handle microseconds!!!  
 *  
 *========================================================================**/

void	eat_and_sleep(t_filo *filo)
{
	get_time_now(&filo->meal_time);
	xpress_mssg(filo, eating);
	usleep(filo->data->tt_eat * 1000);
	xpress_mssg(filo, sleeping);
	usleep(filo->data->tt_sleep * 1000);
	filo->meals_taken++;
}

int	filo_can_eat(t_filo *filo)
{
	int	can_eat;

	can_eat = 1;
	// pthread_mutex_lock(&filo->data->auth_tab_mtx);
	// can_eat = filo->data->auth_tab[0][filo->id];
	// pthread_mutex_unlock(&filo->data->auth_tab_mtx);
	return (can_eat);
}

void	*filo_rtn(void *arg)
{
	t_filo			*filo;
	long int		time_now;

	time_now = 0;
	filo = (t_filo *)arg;
	xpress_mssg(filo, got_born);
	while (time_now < (filo->meal_time + filo->data->tt_die))
	{
		filo = add_id_to_auth_lst(filo);
		if (filo_can_eat(filo))
			eat_and_sleep(filo);
		if (filo->meals_taken == filo->data->max_meals)
		{
			pthread_mutex_lock(&filo->data->auth_tab_mtx);
			filo->data->auth_tab[0][filo->id] = -2;
			pthread_mutex_unlock(&filo->data->auth_tab_mtx);
			return (NULL);
		}
		if (one_filo_died(filo->data))
			return (NULL);
		get_time_now(&time_now);
	}
	xpress_mssg(filo, dead);
	filo_dies(filo);
	return (NULL);
}

/**========================================================================
 *                           coor_rtn
 *! it could be that the filo threads have not signed in to the auth_tab yet
 *! when routine starts. Could be useful to check auth state at start
 *! (philo: pthread_mutex_trylock: Assertion `robust' failed.)
 *========================================================================**/
void	*coor_rtn(void *arg)
{
	t_data	*data;
	int		i;
	int		j;

	data = (t_data *)arg;
	j = 0;
	while (1)
	{
		usleep(500);
		if (one_filo_died(data))
			break ;
		if (all_filos_are_out(data))
			break ;
		j++;
	}
	return (NULL);
}
