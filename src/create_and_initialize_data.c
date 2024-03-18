/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_initialize_data.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:49:03 by dan               #+#    #+#             */
/*   Updated: 2024/03/18 07:38:35 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft.h"
#include <limits.h>
#include <sys/time.h>

int		create_and_initialize_data(t_Data **data, char **argv);
int		alloc_memory_for_data(t_Data **data, char **argv);
long	time_to_ms(struct timeval time_struct);
void	add_argv_data(t_Data **data, char **argv);
int		initialize_mutex(t_Data **data);
void	initialize_filos(t_Data **data);

/**========================================================================
 *                           create_and_initialize_data
 *========================================================================**/
int	create_and_initialize_data(t_Data **data, char **argv)
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
int	alloc_memory_for_data(t_Data **data, char **argv)
{
	(*data) = (t_Data *)ft_calloc(1, sizeof(t_Data));
	add_argv_data(data, argv);
	(*data)->filo = (t_filo *)ft_calloc((*data)->fil_nbr, sizeof(t_filo));
	(*data)->auth_tab = (int *)ft_calloc((*data)->fil_nbr + 1, sizeof(int));
	(*data)->fork = (pthread_mutex_t *)ft_calloc((*data)->fil_nbr,
			sizeof(pthread_mutex_t));
	if (!*data || !(*data)->filo || !(*data)->auth_tab || !(*data)->fork)
		return (0);
	return (1);
}

/**========================================================================
 *                           add_argv_data
 *========================================================================**/
void	add_argv_data(t_Data **data, char **argv)
{
	(*data)->fil_nbr = ft_atoi(argv[1]);
	(*data)->tt_die = ft_atoi(argv[2]);
	(*data)->tt_eat = ft_atoi(argv[3]);
	(*data)->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*data)->max_meals = ft_atoi(argv[5]);
	else
		(*data)->max_meals = INT_MAX;
}

/**========================================================================
 *                           initialize_mutex
 *========================================================================**/
int	initialize_mutex(t_Data **data)
{
	int	i;

	if (pthread_mutex_init(&((*data)->auth_mtx), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&((*data)->print_mtx), NULL) != 0)
		return (0);
	i = 0;
	while (i < (*data)->fil_nbr)
	{
		if (pthread_mutex_init(&((*data)->fork[i]), NULL) != 0)
			return (0);
		if (pthread_mutex_init(&((*data)->filo[i].can_eat_mtx), NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

/**========================================================================
 *                           initialize_filos
 *========================================================================**/
void	initialize_filos(t_Data **data)
{
	int				i;
	struct timeval	now;

	i = 0;
	while (i < (*data)->fil_nbr)
	{
		gettimeofday(&now, NULL);
		(*data)->filo[i].meal_time = time_to_ms(now);
		(*data)->filo[i].data = *data;
		i++;
	}
}
