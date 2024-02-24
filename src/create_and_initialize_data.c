/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_initialize_data.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:39:09 by dsylvain          #+#    #+#             */
/*   Updated: 2024/02/24 10:44:23 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_right_fork_num(int i, int fil_num)
{
	int rf_num;
	
	rf_num = i + 1;
	if (i == fil_num - 1)
		rf_num = 0;
	return (rf_num);
}

s_Data	*create_and_initialize_data(s_Data *data, char **argv)
{
	int	i;

	// create base structs
	
	data = (s_Data *)ft_calloc(1, sizeof(s_Data));
	if(data == NULL)
		return (display_error("mon Error\n"), NULL);
	data->fil_num = ft_atoi(argv[1]);

	// philos creation
	data->filos = (s_Philosopher **)ft_calloc(data->fil_num + 1, sizeof(s_Philosopher *));
	if (data->filos == NULL)
		return (free_data(data), display_error("Error\n"), NULL);
	i = 0;
	while (i < data->fil_num)
	{
		data->filos[i] = (s_Philosopher *)ft_calloc(1, sizeof(s_Philosopher));
		if (data->filos[i] == NULL)
			return (free_data(data), display_error("Error\n"), NULL);
		i++;
	}
	data->filos[i] = NULL;
	
	// tab creation
	data->tab = (int **)ft_calloc(data->fil_num + 1, sizeof(int *));
	if (data->tab == NULL)
		return (free_data(data), display_error("Error\n"), NULL);
	i = 0;
	while (i < data->fil_num)
	{
		data->tab[i] = (int *)ft_calloc(data->fil_num + 1, sizeof(int));
		if (data->tab[i] == NULL)
			return (free_data(data), display_error("Error\n"), NULL);
		data->tab[data->fil_num] = NULL;
		i++;
	}
	data->tab[i] = NULL;

	// tab initialization
	// data->tab[0] : forks. 1 = unused, 0 = in use.
	// data->tab[1] : filos meals state. starts at 0.
	
	i = 0;
	while (i < data->fil_num)
	{
		data->tab[0][i] = 1;
		data->tab[1][i] = 0;
		i++;
	}
	update_meal_auth(&data);
	

	// philos initialization
	i = 0;
	while (i < data->fil_num)
	{
		data->filos[i]->id = i;
		data->filos[i]->meals_taken = &data->tab[1][i];
		data->filos[i]->has_slept = true;
		data->filos[i]->time_to_die = ft_atoi(argv[2]);
		data->filos[i]->meal_auth = &data->tab[1][i];
		data->filos[i]->left_fork = &data->tab[0][i];
		data->filos[i]->right_fork = &data->tab[0][get_right_fork_num(i, data->fil_num)];
		i++;
	}
	
	display_philos(data);

	
	
	return (data);
}