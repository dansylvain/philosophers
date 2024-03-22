/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/22 18:53:12 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define LAST_LONGER 5000

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
	pthread_mutex_lock(&filo->data->fork[filo->id]);
	pthread_mutex_lock(&filo->data->fork[filo->id + 1 % filo->data->fil_nbr]);
	usleep(filo->data->tt_eat * 1000);
	pthread_mutex_unlock(&filo->data->fork[filo->id]);
	pthread_mutex_unlock(&filo->data->fork[filo->id + 1 % filo->data->fil_nbr]);
	xpress_mssg(filo, sleeping);
	usleep(filo->data->tt_sleep * 1000);
	filo->is_subscribed = false;
	return (filo);
}

int	filo_can_eat(t_filo *filo)
{
	int	yes_or_no;

	yes_or_no = 0;
	pthread_mutex_lock(&filo->can_eat_mtx);
	if (filo->can_eat == true)
		yes_or_no = 1;
	pthread_mutex_unlock(&filo->can_eat_mtx);
	return (yes_or_no);
}

void	subscribe_to_auth_tab(t_filo *filo)
{
	int	i;

	pthread_mutex_lock(&filo->data->auth_tab_mtx);
	i = 0;
	while (filo->data->auth_tab[i] > -1 && i < filo->data->fil_nbr)
		i++;
	filo->data->auth_tab[i] = filo->id;
	pthread_mutex_unlock(&filo->data->auth_tab_mtx);
	filo->is_subscribed = true;
}


t_data	*authorize_next_thread_to_eat(t_data *data)
{
	int	i;
	int	id;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	int	l_fork_status;
	int	r_fork_status;

	i = 0;
	while (i < data->fil_nbr)
	{
		// get eligible filo id
		pthread_mutex_lock(&data->auth_tab_mtx);
		if (data->auth_tab[0] < 0)
			return (data);
		l_fork = &data->fork[data->auth_tab[0]];
		r_fork = &data->fork[data->auth_tab[0] + 1 % data->fil_nbr];
		l_fork_status = pthread_mutex_trylock(l_fork);	
		r_fork_status = pthread_mutex_trylock(r_fork);
		if (l_fork_status == 0)
			pthread_mutex_unlock(l_fork);
		if (r_fork_status == 0)
			pthread_mutex_unlock(r_fork);
		if (l_fork_status != 0 || r_fork_status != 0)
			return (pthread_mutex_unlock(&data->auth_tab_mtx), data);
		id = data->auth_tab[0];
		pthread_mutex_unlock(&data->auth_tab_mtx);
		
		

		// give filo authorization to eat
		pthread_mutex_lock(&data->filo[id].can_eat_mtx);
		data->filo[id].can_eat = true;
		pthread_mutex_unlock(&data->filo[id].can_eat_mtx);


		// unsign filo from auth_lst
		i += 1;
		while (i < data->fil_nbr + 1)
		{
			data->auth_tab[i - 1] = data->auth_tab[i];
			i++;
		}
		
		// cut the crap
		return (data);
	}
}

void	display_auth_tab(t_data *data)
{
	int i;
	
	i = 0;
	pthread_mutex_lock(&data->print_mtx);
	while (i < data->fil_nbr)
		printf("%i ", data->auth_tab[i++]);
	printf("\n");
	pthread_mutex_unlock(&data->print_mtx);
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
		if (filo->is_subscribed == false)
			subscribe_to_auth_tab(filo);
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
	int		j;

	data = (t_data *)arg;
	j = 0;
	while (1)
	{
		usleep(data->tt_eat * 1000);
		data = authorize_next_thread_to_eat(data);		
		display_auth_tab(data);
		// j++;
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
