/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:07 by dan               #+#    #+#             */
/*   Updated: 2024/02/23 21:00:53 by dan              ###   ########.fr       */
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
			free(data->tab[i++]);
		free(data->tab);
	}
	if (data->filos)
	{
		while (data->filos[i])
			free(data->filos[i++]);
		free(data->filos);
	}
	free(data);
	i = 0;
}