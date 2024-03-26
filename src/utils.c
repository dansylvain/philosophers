/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 07:27:02 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 12:58:40 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s);

int		check_input(int argc, char **argv);
void	free_data(t_data *data);
void	display_error(char *str);
int		create_and_initialize_data(t_data **data, char **argv);
t_data	*run_threads(t_data *data);
void	xpress_mssg(t_filo *filo, t_mssg mssg);
long	time_to_ms(struct timeval time_struct);
t_data	*run_threads(t_data *data);
void	get_time_now(long int	*time_now);
int		time_is_up(t_filo *filo);
void	check_death_condition(t_filo *filo);
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

t_data	*run_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->fil_nbr)
	{
		data->filo[i].id = i;
		if (pthread_create(&data->filo[i].filo, NULL,
				filo_rtn, &data->filo[i]) != 0)
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
	return (data);
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
