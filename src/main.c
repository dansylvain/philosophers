/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/20 08:02:04 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <pthread.h>
# include <sys/time.h>
#include <unistd.h>

#define LAST_LONGER 5000

int		check_input(int argc, char **argv);
void	free_data(t_Data *data);
void	display_error(char *str);
int		create_and_initialize_data(t_Data **data, char **argv);
t_Data	*run_threads(t_Data *data);
void	xpress_mssg(t_filo *filo, mssg mssg);
long	time_to_ms(struct timeval time_struct);
t_Data *run_threads(t_Data *data);

t_filo	*eat_and_sleep(t_filo *filo)
{
	struct timeval now;
	t_Data *data;
	
	data = filo->data;
	gettimeofday(&now, NULL);
	filo->meal_time = time_to_ms(now);
	//! lock forks here
	xpress_mssg(filo, eating);
	usleep(data->tt_eat * LAST_LONGER);
	//! unlock forks here
	xpress_mssg(filo, sleeping);
	usleep(data->tt_sleep * LAST_LONGER);
	pthread_mutex_lock(&filo->can_eat_mtx);
	filo->can_eat = 1;
	pthread_mutex_unlock(&filo->can_eat_mtx);
	return (filo);
}

int	check_if_filo_can_eat(t_filo *filo)
{
	int	filo_auth;

	filo_auth = 0;
	// printf("entering check_if_filo_can_eat\n");
	pthread_mutex_lock(&filo->can_eat_mtx);
	if (filo->can_eat == true)
		filo_auth = 1;
	else if (filo->can_eat == false)
		filo_auth = 0;
	pthread_mutex_unlock(&filo->can_eat_mtx);
	return (filo_auth);
}


/**========================================================================
 *                           sign_in_to_auth_lst
 *? commented text to be tested. could reduce code qtty 
 *========================================================================**/
void	sign_in_to_auth_lst(t_filo *filo)
{
	int				i;
	int				*tab;
	pthread_mutex_t	*mtx;
	
	mtx = &filo->data->auth_tab_mtx;
	tab = filo->data->auth_tab;
	pthread_mutex_lock(mtx);
	i = 0;
	while (tab[i] && i < filo->data->fil_nbr)
		i++;
	tab[i] = filo->id;
	pthread_mutex_unlock(mtx);
	filo->is_signed_in = true;

}

void	*filo_rtn(void *arg)
{
	t_filo 		*filo;
	long int	time_now;
	struct timeval now;

	filo = (t_filo *)arg;
	xpress_mssg(filo, got_born);
	while (time_now < (filo->meal_time + filo->data->tt_die))
	{
		if (!filo->is_signed_in)
			sign_in_to_auth_lst(filo);
		if (check_if_filo_can_eat(filo))
			filo = eat_and_sleep(filo);
		gettimeofday(&now, NULL);
		time_now = time_to_ms(now);
	}
	xpress_mssg(filo, dead);
	return (NULL);
}

void	*coor_rtn(void *arg)
{
	t_Data *data;
	int	i;
	
	data = (t_Data *)arg;
	while (1)
	{
		sleep(1);
		pthread_mutex_lock(&data->filo[1].can_eat_mtx);
		data->filo[1].can_eat = true;
		pthread_mutex_unlock(&data->filo[1].can_eat_mtx);
		pthread_mutex_lock(&data->print_mtx);
		printf("Auth tab: \n");
		i = 0;
		while (i < data->fil_nbr)
			printf("%i ", data->auth_tab[i++]);
		printf("\n");
		pthread_mutex_unlock(&data->print_mtx);	
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_Data	*data;
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


