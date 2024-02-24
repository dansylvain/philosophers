/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:35:11 by dan               #+#    #+#             */
/*   Updated: 2024/02/23 21:11:24 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int				fil_num;
	int				i;
	s_Data			*data;
	

	
	// input check
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	
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
		data->filos[i]->meals_taken = 0;
		data->filos[i]->has_slept = 0;
		data->filos[i]->time_to_die = ft_atoi(argv[2]);
		i++;
	}
	data->filos[i] = NULL;
	
	// tab creation
	data->tab = (int **)ft_calloc(fil_num + 1, sizeof(int *));
	if (data->tab == NULL)
		return (free_data(data), display_error("Error\n"), 1);


	free_data(data);
	return (0);
}

