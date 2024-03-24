/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:39:03 by dan               #+#    #+#             */
/*   Updated: 2024/03/24 20:09:51 by dan              ###   ########.fr       */
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
int		filo_has_taken_all_his_meals(t_filo *filo);
int		filo_can_eat(t_filo *filo);
void	change_filo_state(t_filo *filo, int state);
t_data	*authorize_filos_to_eat(t_data *data);

/**========================================================================
 *                             DON'T FORGET!!!
 *! beware of units!!!  
 *! time is converted to ms for input and display purpose 
 *! but funcs handle microseconds!!!  
 *  
 *========================================================================**/

void	eat_and_sleep(t_filo *filo)
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;

	lfork = &filo->data->fork[filo->id];
	rfork = &filo->data->fork[(filo->id + 1) % filo->data->fil_nbr];
	get_time_now(&filo->meal_time);
	pthread_mutex_lock(lfork);
	pthread_mutex_lock(rfork);
	change_filo_state(filo, 2);
	xpress_mssg(filo, eating);
	usleep(filo->data->tt_eat * 1000);
	pthread_mutex_unlock(lfork);
	pthread_mutex_unlock(rfork);
	change_filo_state(filo, 3);
	xpress_mssg(filo, sleeping);
	usleep(filo->data->tt_sleep * 1000);
	change_filo_state(filo, 0);
	xpress_mssg(filo, thinking);
	filo->is_registered = 0;
	filo->meals_taken++;
}

void	*filo_rtn(void *arg)
{
	t_filo		*filo;
	long int	time_now;

	time_now = 0;
	filo = (t_filo *)arg;
	while (time_now < (filo->meal_time + filo->data->tt_die))
	{
		if (filo->is_registered == 0)
			add_id_to_auth_lst(filo);
		if (filo_can_eat(filo))
			eat_and_sleep(filo);
		if (filo_has_taken_all_his_meals(filo))
			return (NULL);
		if (one_filo_died(filo->data))
			return (NULL);
		get_time_now(&time_now);
	}
	xpress_mssg(filo, dead);
	change_filo_state(filo, -1);
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
		if (one_filo_died(data))
			break ;
		if (all_filos_are_out(data))
			break ;
		authorize_filos_to_eat(data);
		j++;
	}
	return (NULL);
}
