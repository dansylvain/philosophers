/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/24 07:18:02 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define LAST_LONGER 5000

int		one_filo_died(t_data *data);
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
void	filo_dies(t_filo *filo);
void	display_auth_tab(t_data *data);
t_filo	*add_id_to_auth_lst(t_filo *filo);

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
		printf("filo->meals_taken: %i == filo->data->max_meals: %i\n", filo->meals_taken, filo->data->max_meals);
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

int forks_are_available(t_data *data, int id)
{
    int l_fork_status;
    int r_fork_status;

    l_fork_status = pthread_mutex_trylock(&data->fork[id]);
    if (l_fork_status != 0)
        return (0);
	usleep(100);
    r_fork_status = pthread_mutex_trylock(&data->fork[(id + 1) % data->fil_nbr]);
    if (r_fork_status != 0)
	{
        
        return (pthread_mutex_unlock(&data->fork[id]), usleep(100), 0);
    }
    return 1;
}
t_data	*authorize_filos_to_eat(t_data *data)
{
	int	i;
	int	id;

	usleep(500);
	i = 0;
	if (pthread_mutex_trylock(&data->auth_tab_mtx))
		return (data);
	while (i < data->fil_nbr)
	{
		id = data->auth_tab[1][i];
		if (forks_are_available(data, id))
			data->auth_tab[0][id] = 1;
		i++;
	}
	pthread_mutex_unlock(&data->auth_tab_mtx);
	return (data);
}

int	all_filo_are_out(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_lock(&data->auth_tab_mtx);
	while (i < data->fil_nbr)
	{
		if (data->auth_tab[0][i] != -2)
			return (pthread_mutex_unlock(&data->auth_tab_mtx), 0);
		i++;
	}
	pthread_mutex_unlock(&data->auth_tab_mtx);
	return (1);
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
	while (j < 4)
	{
		usleep(500);
		// authorize_filos_to_eat(data);
		// if (j % 1000 == 0)
		// {
		// 	display_auth_tab(data);
		// }
		if (one_filo_died(data))
			break ;
		if (all_filo_are_out(data))
			break ;
		j++;
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
	data = run_threads(data);
	if (data == NULL)
		return (free_data(data), display_error("Error\n"), 3);
	destroy_mutexes(data);
	free_data(data);
	return (0);
}
