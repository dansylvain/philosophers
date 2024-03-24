/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_toutines_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:04:11 by dan               #+#    #+#             */
/*   Updated: 2024/03/24 19:30:21 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	filo_can_eat(t_filo *filo)
{
	int	can_eat;

	can_eat = 0;
	pthread_mutex_lock(&filo->state_mtx);
	if (filo->state == 1)
		can_eat = 1;
	pthread_mutex_unlock(&filo->state_mtx);
	return (can_eat);
}

void	change_filo_state(t_data *data, int filo_id, int state)
{
	pthread_mutex_lock(&data->filo[filo_id].state_mtx);
	data->filo[filo_id].state = state;
	pthread_mutex_unlock(&data->filo[filo_id].state_mtx);
}

int	no_neighbours_are_eating(t_data *data, int id)
{
	int	is_not_eating;
	int	l_neighbour;
	int	r_neighbour;

	is_not_eating = 1;
	l_neighbour = (id + 1) % data->fil_nbr;
	if (id == 0)
		r_neighbour = data->fil_nbr - 1;
	else
		r_neighbour = id - 1;
	pthread_mutex_lock(&data->auth_tab_mtx);
	if (data->auth_tab[0][l_neighbour] == 2)
		is_not_eating = 0;
	if (data->auth_tab[0][r_neighbour] == 2)
		is_not_eating = 0;
	pthread_mutex_unlock(&data->auth_tab_mtx);
	return (is_not_eating);
}

void	update_auth_lst_queue(t_data *data, int id)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->auth_tab_mtx);
	while (data->auth_tab[1][i] != id)
		i++;
	while (data->auth_tab[1][i + 1] != -1)
	{
		data->auth_tab[1][i] = data->auth_tab[1][i + 1];
		i++;
	}
	data->auth_tab[1][i] = -1;
	pthread_mutex_unlock(&data->auth_tab_mtx);
}

t_data	*authorize_filos_to_eat(t_data *data)
{
	int	i;
	int	id;

	i = 0;
	while (i < data->fil_nbr)
	{
		pthread_mutex_lock(&data->auth_tab_mtx);
		id = data->auth_tab[1][i];
		pthread_mutex_unlock(&data->auth_tab_mtx);
		if (data->fil_nbr == 1)
			return (0);
		if (data->auth_tab[0][id] == 0 && no_neighbours_are_eating(data, id))
		{
			change_filo_state(data, id, 1);
			update_auth_lst_queue(data, id);
		}
		i++;
	}
	return (data);
}
