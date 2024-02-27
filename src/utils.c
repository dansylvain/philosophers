/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:07 by dan               #+#    #+#             */
/*   Updated: 2024/02/27 16:15:17 by dan              ###   ########.fr       */
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
	int	i;
	
	*data = (t_Data *)ft_calloc(1, sizeof(t_Data));
	if (*data == NULL)
		return (0);
	(*data)->fil_num = ft_atoi(argv[1]);
	(*data)->tt_die = ft_atoi(argv[2]);
	(*data)->tt_eat = ft_atoi(argv[3]);
	(*data)->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*data)->max_meals = ft_atoi(argv[5]);
	(*data)->id = (int *)ft_calloc((*data)->fil_num, sizeof(int));
	(*data)->fork = (int *)ft_calloc((*data)->fil_num, sizeof(int));
	(*data)->meal_count = (int *)ft_calloc((*data)->fil_num, sizeof(int));
	(*data)->filo = (pthread_t *)ft_calloc((*data)->fil_num, sizeof(pthread_t));
	if (!(*data)->id || !(*data)->fork || !(*data)->meal_count || !(*data)->filo)
		return (0);
	i = 0;
	while (i < (*data)->fil_num)
	{
		(*data)->fork[i] = 1;
		(*data)->meal_count[i] = 0;
		i++; 
	}
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
	if (data->filo)	
		free(data->filo);
	if (data)
		free(data);
}

void	display_filo(t_Data *data)
{
	ft_printf("id: %i\n", *data->id);
	ft_printf("fil_num: %i\n", data->fil_num);
	ft_printf("tt_die: %i\n", data->tt_die);
	ft_printf("tt_eat: %i\n", data->tt_eat);
	ft_printf("tt_sleep: %i\n", data->tt_sleep);
	ft_printf("max_meals: %i\n", data->max_meals);
	ft_printf("meal count: %i\n", data->meal_count[*data->id]);
	ft_printf("left fork: %i\n", data->fork[*data->id]);
	if (*data->id == data->fil_num - 1)
		ft_printf("right fork: %i\n", data->fork[0]);
	else
		ft_printf("right fork: %i\n", data->fork[*data->id + 1]);
}
