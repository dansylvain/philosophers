/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 07:27:02 by dan               #+#    #+#             */
/*   Updated: 2024/03/21 11:55:39 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>

void	*coor_rtn(void *arg);
void	*filo_rtn(void *arg);
void	get_time_now(long int	*time_now);

void	free_data(t_data *data)
{
	free(data->auth_tab);
	free(data->fork);
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
	get_time_now(&t);
	mut = &filo->data->print_mtx;
	pthread_mutex_lock(mut);
	printf("%li %i %s\n", t, filo->id, mssg_str);
	pthread_mutex_unlock(mut);
}

t_data	*run_threads(t_data *data)
{
	int	i;

	if (pthread_create(&data->coor, NULL, coor_rtn, data) != 0)
		return (NULL);
	i = 0;
	while (i < data->fil_nbr)
	{
		data->filo[i].id = i;
		if (pthread_create(&data->filo[i].filo,
				NULL, filo_rtn, &data->filo[i]) != 0)
			return (NULL);
		i++;
	}
	i = 0;
	while (i < data->fil_nbr)
	{
		if (pthread_join(data->filo[i].filo, NULL) != 0)
			return (NULL);
		i++;
	}
	if (pthread_join(data->coor, NULL) != 0)
		return (NULL);
	return (data);
}

void	get_time_now(long int	*time_now)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	*time_now = now.tv_sec * 1000 + now.tv_usec;
}
