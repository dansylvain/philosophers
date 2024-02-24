/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:07 by dan               #+#    #+#             */
/*   Updated: 2024/02/24 08:36:06 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_error(char *str)
{
	if (write (2, str, ft_strlen(str)) == -1)
		perror("display_error");
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
