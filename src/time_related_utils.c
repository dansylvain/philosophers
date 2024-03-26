/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_related_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:01:17 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 13:37:11 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time_related_utils.h"

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

int	time_is_up(t_filo *filo)
{
	struct timeval	now;
	long int		time_now;

	get_time_now(&time_now);
	if (time_now > filo->meal_time + filo->data->tt_die)
		return (1);
	return (0);
}
