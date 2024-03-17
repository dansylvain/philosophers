/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_initialize_data.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 07:29:16 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 08:29:58 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>
#include "libft.h"

int	create_and_initialize_data(t_Data **data, char **argv)
{
	int	i;
	
	*data = (t_Data *)ft_calloc(1, 	sizeof(t_Data));
	(*data)->fil_nbr = ft_atoi(argv[1]);
	if (!(*data))
		return (0);
	(*data)->tt_die = ft_atoi(argv[2]);
	(*data)->tt_eat = ft_atoi(argv[3]);
	(*data)->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*data)->max_meals = ft_atoi(argv[5]);
	else
		(*data)->max_meals = INT_MAX;
	(*data)->filo = (t_filo *)ft_calloc((*data)->fil_nbr, sizeof(t_filo));
	if (!(*data)->filo)
		return (0);
	i = 0;
	
	
	while (i < (*data)->fil_nbr)
	{
		(*data)->filo[i].data = *data;
		//do something
		i++;
	}

	return (1);
}