/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:35:11 by dan               #+#    #+#             */
/*   Updated: 2024/02/24 09:56:53 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_meal_auth(s_Data **data)
{
	int	i;
	
	i = 0;
	while ((*data)->tab[1][i])
	{
		if ((*data)->tab[1][i] > (*data)->meal_auth)
			(*data)->meal_auth = (*data)->tab[1][i];
		i++;
	}	
}

int	get_right_fork_num(int i, int fil_num)
{
	int rf_num;
	
	rf_num = i + 1;
	if (i == fil_num - 1)
		rf_num = 0;
	return (rf_num);
}

void	display_philo(s_Philosopher *filo)
{
	ft_printf("filo %i\n", filo->id);
	ft_printf("filo->meals_taken: %i\n", *filo->meals_taken);
	ft_printf("filo->has_slept: %i\n", filo->has_slept);
	ft_printf("filo->time_to_die: %i\n", filo->time_to_die);
	ft_printf("filo->meal_auth: %i\n", *filo->meal_auth);
	ft_printf("filo->left_fork: %i\n", *filo->left_fork);
	ft_printf("filo->right_fork: %i\n", *filo->right_fork);
}

int	main(int argc, char **argv)
{
	int				fil_num;
	int				i;
	s_Data			*data;
	
	// input check
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	
	// create base structs
	fil_num = ft_atoi(argv[1]);
	
	data = (s_Data *)ft_calloc(1, sizeof(s_Data));
	if(data == NULL)
		return (display_error("mon Error\n"), 1);

	// philos creation
	data->filos = (s_Philosopher **)ft_calloc(fil_num + 1, sizeof(s_Philosopher *));
	if (data->filos == NULL)
		return (free_data(data), display_error("Error\n"), 1);
	i = 0;
	while (i < fil_num)
	{
		data->filos[i] = (s_Philosopher *)ft_calloc(1, sizeof(s_Philosopher));
		if (data->filos[i] == NULL)
			return (free_data(data), display_error("Error\n"), 1);
		i++;
	}
	data->filos[i] = NULL;
	
	// tab creation
	data->tab = (int **)ft_calloc(fil_num + 1, sizeof(int *));
	if (data->tab == NULL)
		return (free_data(data), display_error("Error\n"), 1);
	i = 0;
	while (i < fil_num)
	{
		data->tab[i] = (int *)ft_calloc(fil_num + 1, sizeof(int));
		if (data->tab[i] == NULL)
			return (free_data(data), display_error("Error\n"), 1);
		data->tab[fil_num] = NULL;
		i++;
	}
	data->tab[i] = NULL;

	// tab initialization
	// data->tab[0] : forks. 1 = unused, 0 = in use.
	// data->tab[1] : filos meals state. starts at 0.
	
	i = 0;
	while (i < fil_num)
	{
		data->tab[0][i] = 1;
		data->tab[1][i] = 0;
		i++;
	}
	update_meal_auth(&data);
	

	// philos initialization
	i = 0;
	while (i < fil_num)
	{
		data->filos[i]->id = i;
		data->filos[i]->meals_taken = &data->tab[1][i];
		data->filos[i]->has_slept = true;
		data->filos[i]->time_to_die = ft_atoi(argv[2]);
		data->filos[i]->meal_auth = &data->tab[1][i];
		data->filos[i]->left_fork = &data->tab[0][i];
		data->filos[i]->right_fork = &data->tab[0][get_right_fork_num(i, fil_num)];
		i++;
	}
}

