/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_conditions_funcs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/24 20:38:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>

int	one_filo_died(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->filo[i].state_mtx);
	while (i < data->fil_nbr)
	{
		if (data->filo[i].state == -1)
			return (pthread_mutex_unlock(&data->filo[i].state_mtx), 1);
		pthread_mutex_unlock(&data->filo[i].state_mtx);
		i++;
	}
	pthread_mutex_unlock(&data->auth_tab_mtx);
	return (0);
}

int	all_filos_are_out(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->filo[i].state_mtx);
	while (i < data->fil_nbr)
	{
		if (data->filo[i].state != -2)
			return (pthread_mutex_unlock(&data->filo[i].state_mtx), 0);
		i++;
	}
	pthread_mutex_unlock(&data->filo[i].state_mtx);
	return (1);
}
