/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_initialize_data.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:49:03 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 13:33:47 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_and_initialize_data.h"

/**========================================================================
 *                           create_and_initialize_data
 *========================================================================**/
int	create_and_initialize_data(t_data **data, char **argv)
{
	if (alloc_memory_for_data(data, argv) == 0)
		return (0);
	if (initialize_mutex(data) == 0)
		return (0);
	initialize_filos(data);
	return (1);
}

/**========================================================================
 *                           alloc_memory_for_data
 *========================================================================**/
int	alloc_memory_for_data(t_data **data, char **argv)
{
	(*data) = (t_data *)ft_calloc(1, sizeof(t_data));
	add_argv_data(data, argv);
	(*data)->filo = (t_filo *)ft_calloc((*data)->fil_nbr, sizeof(t_filo));
	(*data)->fork = (pthread_mutex_t *)ft_calloc((*data)->fil_nbr,
			sizeof(pthread_mutex_t));
	if (!*data || !(*data)->filo || !(*data)->fork)
		return (0);
	return (1);
}

/**========================================================================
 *                           add_argv_data
 *========================================================================**/
void	add_argv_data(t_data **data, char **argv)
{
	(*data)->fil_nbr = ft_atoi(argv[1]);
	(*data)->tt_die = ft_atoi(argv[2]);
	(*data)->tt_eat = ft_atoi(argv[3]);
	(*data)->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*data)->max_meals = ft_atoi(argv[5]);
	else
		(*data)->max_meals = INT_MAX;
	(*data)->stop = false;
}

/**========================================================================
 *                           initialize_mutex
 *========================================================================**/
int	initialize_mutex(t_data **data)
{
	int	i;

	if (pthread_mutex_init(&((*data)->print_mtx), NULL) != 0)
		return (0);
	i = 0;
	while (i < (*data)->fil_nbr)
	{
		if (pthread_mutex_init(&((*data)->fork[i]), NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

/**========================================================================
 *                           initialize_filos
 *========================================================================**/
void	initialize_filos(t_data **data)
{
	int				i;
	struct timeval	now;

	i = 0;
	while (i < (*data)->fil_nbr)
	{
		gettimeofday(&now, NULL);
		(*data)->filo[i].meal_time = time_to_ms(now);
		(*data)->filo[i].meals_taken = 0;
		(*data)->filo[i].max_meals = (*data)->max_meals;
		(*data)->filo[i].data = *data;
		(*data)->filo[i].lfork_taken = false;
		(*data)->filo[i].rfork_taken = false;
		i++;
	}
	(*data)->starting_time = time_to_ms(now);
}
