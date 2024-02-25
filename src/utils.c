/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:07 by dan               #+#    #+#             */
/*   Updated: 2024/02/25 10:41:56 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_error(char *str)
{
	if (write (2, str, ft_strlen(str)) == -1)
		perror("display_error");
}

int	create_data_struct(t_Data **data, char **argv)
{
	*data = (t_Data *)malloc(sizeof(t_Data));
	if (*data == NULL)
		return (0);
	(*data)->fil_num = ft_atoi(argv[1]);
	(*data)->tt_die = ft_atoi(argv[2]);
	(*data)->tt_eat = ft_atoi(argv[3]);
	(*data)->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*data)->max_meals = ft_atoi(argv[5]);
	(*data)->id = (int *)malloc(sizeof(int) * (*data)->fil_num);
	(*data)->fork = (int *)malloc(sizeof(int) * (*data)->fil_num);
	(*data)->meal_count = (int *)malloc(sizeof(int) * (*data)->fil_num);
	if (!(*data)->id || !(*data)->fork || !(*data)->meal_count)
		return (0);
	return (1);
}

void	free_data(t_Data *data)
{
	if (data->id)
		free(data->id);
	if (data->fork)
		free(data->fork);
	if (data->meal_count)	
		free(data->meal_count);
	if (data)
		free(data);
}
