/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 07:27:02 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 10:55:26 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n);

size_t	ft_strlen(const char *s);

void	*coor_rtn(void *arg);
void	*filo_rtn(void *arg);

void	free_data(t_data *data)
{
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

void	get_time_now(long int	*time_now)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	*time_now = time_to_ms(now);
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
	gettimeofday(&now, NULL);
	t = time_to_ms(now) - filo->data->starting_time;
	mut = &filo->data->print_mtx;
	pthread_mutex_lock(mut);
	printf("%li %i %s\n", t, filo->id + 1, mssg_str);
	pthread_mutex_unlock(mut);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb * size / size != nmemb)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = (unsigned char)c;
	return (s);
}
