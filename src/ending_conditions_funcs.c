/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_conditions_funcs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/24 11:32:11 by dan              ###   ########.fr       */
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

int	all_filos_are_out(t_data *data)
{
	int	i;

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
