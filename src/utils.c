/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 07:27:02 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 10:23:29 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include <errno.h>
# include <sys/time.h>

void	free_data(t_Data *data)
{
	free(data->filo);
	free(data);
}

void	display_error(char *str)
{
	if (write (2, str, ft_strlen(str)) == -1)
		perror("display_error");
}

long	time_to_ms(struct timeval time_struct)
{
	return (time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000);
}

void	xpress_mssg(t_filo *filo, mssg mssg)
{
	char 			*mssg_str;
	long int		t;
	struct timeval	now;
	pthread_mutex_t *mut;

	if (mssg == take_fork)
		mssg_str = "has taken a fork";
	if (mssg == eating)
		mssg_str = "is eating";
	if (mssg == sleeping)
		mssg_str = "is sleeping";
	if (mssg == thinking)
		mssg_str = "is thinking";
	if (mssg == dead)
		mssg_str = "died";
	mut = &filo->data->print_mutex;
	pthread_mutex_lock(mut);
	gettimeofday(&now, NULL);
	t = time_to_ms(now);
	printf("%li %i %s\n", t, filo->id, mssg_str);
	pthread_mutex_unlock(mut);
}
