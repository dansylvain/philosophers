/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:35:11 by dan               #+#    #+#             */
/*   Updated: 2024/02/24 11:20:00 by dsylvain         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	int				i;
	s_Data			*data;
	
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);	
	data = create_and_initialize_data(data, argv);
	if (data == NULL)
		return (free_data(data), display_error("Error\n"), 2);
	display_philos(data);

	free_data(data);
}

