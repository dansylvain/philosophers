/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:54:42 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 12:54:54 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n);
long	time_to_ms(struct timeval time_struct);

size_t	ft_strlen(const char *s);

void	*coor_rtn(void *arg);
void	*filo_rtn(void *arg);

void	xpress_mssg(t_filo *filo, t_mssg mssg)
{
	char			*mssg_str;
	long int		t;
	struct timeval	now;
	pthread_mutex_t	*mut;

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
	if (mssg == got_born)
		mssg_str = "got born";
	gettimeofday(&now, NULL);
	t = time_to_ms(now) - filo->data->starting_time;
	mut = &filo->data->print_mtx;
	pthread_mutex_lock(mut);
	printf("%li %i %s\n", t, filo->id + 1, mssg_str);
	pthread_mutex_unlock(mut);
}

void	check_death_condition(t_filo *filo)
{
	if (filo->data->stop != true)
	{
		usleep(1);
		if (filo->data->stop != true)
		{
			filo->data->stop = true;
			xpress_mssg(filo, dead);
		}
	}
}