/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_initialize_data.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:49:03 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 08:54:23 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "libft.h"
#include <limits.h>

int	create_and_initialize_data(t_Data **data, char **argv)
{
	(*data) = (t_Data *)ft_calloc(1, sizeof(t_Data));
	(*data)->fil_nbr = ft_atoi(argv[1]);
	(*data)->tt_die = ft_atoi(argv[2]);
	(*data)->tt_eat = ft_atoi(argv[3]);
	(*data)->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*data)->max_meals = ft_atoi(argv[5]);
	else
		(*data)->max_meals = INT_MAX;
	
}