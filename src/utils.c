/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:07 by dan               #+#    #+#             */
/*   Updated: 2024/02/24 10:48:48 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_error(char *str)
{
	if (write (2, str, ft_strlen(str)) == -1)
		perror("display_error");
}

void	display_philos(s_Data *data)
{
	int	i;
	
	i = 0;
	while (i < data->fil_num)
	{
		ft_printf("-------------------------\n");
		ft_printf("filo %i\n", data->filos[i]->id);
		ft_printf("filo->meals_taken: %i\n", *data->filos[i]->meals_taken);
		ft_printf("filo->has_slept: %i\n", data->filos[i]->has_slept);
		ft_printf("filo->time_to_die: %i\n", data->filos[i]->time_to_die);
		ft_printf("filo->meal_auth: %i\n", *data->filos[i]->meal_auth);
		ft_printf("filo->left_fork: %i\n", *data->filos[i]->left_fork);
		ft_printf("filo->right_fork: %i\n", *data->filos[i]->right_fork);
		ft_printf("-------------------------\n\n");
		i++;		
	}
}

void	free_data(s_Data *data)
{
	int i;
	
	i = 0;
	if (data->tab)
	{
		while (data->tab[i])
		{
			if (data->tab[i])
				free(data->tab[i++]);
		}
		free(data->tab);
	}
	i = 0;
	if (data->filos)
	{
		while (data->filos[i])
		{
			if (data->filos[i])
				free(data->filos[i++]);
		}
		free(data->filos);
	}
	free(data);
	i = 0;
}
