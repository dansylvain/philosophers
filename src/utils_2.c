/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:44:50 by dan               #+#    #+#             */
/*   Updated: 2024/03/24 07:43:02 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "libft.h"
#include <stdio.h>
#include "philosophers.h"

void	display_error(char *str)
{
	if (write (2, str, ft_strlen(str)) == -1)
		perror("display_error");
}

long	time_to_ms(struct timeval time_struct)
{
	return (time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000);
}

void	get_time_now(long int	*time_now)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	*time_now = time_to_ms(now);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
		free(data->auth_tab[i++]);
	free(data->auth_tab);
	free(data->fork);
	free(data->filo);
	free(data);
}
