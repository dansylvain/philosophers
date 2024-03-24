/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 07:27:02 by dan               #+#    #+#             */
/*   Updated: 2024/03/24 07:31:53 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>

void	*coor_rtn(void *arg);
void	*filo_rtn(void *arg);
void	get_time_now(long int	*time_now);

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
		free(data->auth_tab[i++]);
	free(data->auth_tab);
	free(data->fork);
	free(data->filo);
	free(data);
}

void	xpress_mssg(t_filo *filo, t_mssg mssg)
{
	char			*mssg_str;
	long int		t;
	struct timeval	now;
	pthread_mutex_t	*mut;

	if (mssg == take_fork)
		mssg_str = "has taken a fork";
	if (mssg == eating)
		mssg_str = "is eating";
	if (mssg == sleeping)
		mssg_str = "is sleeping";
	if (mssg == thinking)
		mssg_str = "is thinking";
	if (mssg == dead)
		mssg_str = "died";
	if (mssg == got_born)
		mssg_str = "got born";
	get_time_now(&t);
	mut = &filo->data->print_mtx;
	pthread_mutex_lock(mut);
	printf("%li %i %s\n", t, filo->id, mssg_str);
	pthread_mutex_unlock(mut);
}

t_data	*run_threads(t_data *data)
{
	int	i;

	if (pthread_create(&data->coor, NULL, coor_rtn, data) != 0)
		return (NULL);
	i = 0;
	while (i < data->fil_nbr)
	{
		data->filo[i].id = i;
		if (pthread_create(&data->filo[i].filo,
				NULL, filo_rtn, &data->filo[i]) != 0)
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
	if (pthread_join(data->coor, NULL) != 0)
		return (NULL);
	return (data);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print_mtx);
	i = 0;
	while (i < data->fil_nbr)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
}

int	one_filo_died(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->auth_tab_mtx);
	i = 0;
	while (i < data->fil_nbr)
	{
		if (data->auth_tab[0][i] == -1)
			return (pthread_mutex_unlock(&data->auth_tab_mtx), 1);
		i++;
	}
	pthread_mutex_unlock(&data->auth_tab_mtx);
	return (0);
}

void	filo_dies(t_filo *filo)
{
	pthread_mutex_lock(&filo->data->auth_tab_mtx);
	filo->data->auth_tab[0][filo->id] = -1;
	pthread_mutex_unlock(&filo->data->auth_tab_mtx);
}

int	all_filos_are_out(t_data *data)
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

t_filo	*add_id_to_auth_lst(t_filo *filo)
{
	int	i;
	int	*fil_auth;
	int	fil_nbr;

	fil_nbr = filo->data->fil_nbr;
	i = 0;
	pthread_mutex_lock(&filo->data->auth_tab_mtx);
	fil_auth = filo->data->auth_tab[1];
	while (fil_auth[i] != -1 && i < fil_nbr && fil_auth[i] != filo->id)
		i++;
	fil_auth[i] = filo->id;
	pthread_mutex_unlock(&filo->data->auth_tab_mtx);
	return (filo);
}
