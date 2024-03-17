/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_initialize_data.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:49:03 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 10:29:22 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft.h"
#include <limits.h>
# include <sys/time.h>

long	time_to_ms(struct timeval time_struct);


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

int	create_and_initialize_data(t_Data **data, char **argv)
{
	int	i;
	struct timeval	now;

	(*data) = (t_Data *)ft_calloc(1, sizeof(t_Data));
	add_argv_data(data, argv);
	(*data)->filo = (t_filo *)ft_calloc((*data)->fil_nbr, sizeof(t_filo));
	if (pthread_mutex_init(&((*data)->print_mutex), NULL) != 0)
		return (0);
	i = 0;
	while (i < (*data)->fil_nbr)
	{
		gettimeofday(&now, NULL);
		(*data)->filo[i].meal_time = time_to_ms(now);
		(*data)->filo[i].data = *data;
		i++;
	}
	return (1);
	
}