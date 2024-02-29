/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:07 by dan               #+#    #+#             */
/*   Updated: 2024/02/29 06:55:29 by dsylvain         ###   ########.fr       */
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
	return (1);
}

void	free_data(t_Data *data, t_Thread_args **filo)
{

}

void	display_filo(t_Data *data)
{

}
