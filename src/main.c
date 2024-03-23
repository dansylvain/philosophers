/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/23 11:24:59 by dan              ###   ########.fr       */
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

/**========================================================================
 *                             DON'T FORGET!!!
 *! beware of units!!!  
 *! time is converted to ms for input and display purpose 
 *! but funcs handle microseconds!!!  
 *  
 *========================================================================**/

void	eat_and_sleep(t_filo *filo)
{
	xpress_mssg(filo, eating);
	usleep(filo->data->tt_eat * 1000);
	xpress_mssg(filo, sleeping);
	usleep(filo->data->tt_sleep * 1000);
	
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
		eat_and_sleep(filo);
		get_time_now(&time_now);
	}
	xpress_mssg(filo, dead);
	filo_dies(filo);
	return (NULL);
}

void	display_auth_tab(t_data *data)
{
	int	i;
	int	j;

	
	pthread_mutex_lock(&data->print_mtx);
	pthread_mutex_lock(&data->auth_tab_mtx);
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < data->fil_nbr)
		{
			printf("%3i ", data->auth_tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	
	pthread_mutex_unlock(&data->auth_tab_mtx);
	pthread_mutex_unlock(&data->print_mtx);
	
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
		if (j == 500)
			display_auth_tab(data);
		// pthread_mutex_lock(&data->print_mtx);
		// printf("%i I'm watching you\n", data->all_filos_live);
		// pthread_mutex_unlock(&data->print_mtx);
		usleep(500);
		if (one_filo_died(data))
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
