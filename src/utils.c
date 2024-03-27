/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 07:27:02 by dan               #+#    #+#             */
/*   Updated: 2024/03/27 15:55:11 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**========================================================================
 *                           free_data
 *========================================================================**/
void	free_data(t_data *data)
{
	free(data->fork);
	free(data->filo);
	free(data);
}

/**========================================================================
 *                           display_error
 *========================================================================**/
void	display_error(char *str)
{
	if (write (2, str, ft_strlen(str)) == -1)
		perror("display_error");
}

/**========================================================================
 *                           run_threads
 *========================================================================**/
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
	pthread_mutex_lock(&filo->data->stop_mtx);
	if (filo->data->stop != true)
	{
		usleep(1);
		if (filo->data->stop != true)
		{
			filo->data->stop = true;
			xpress_mssg(filo, dead);
		}
		if (filo->lfork_taken == true)
			pthread_mutex_unlock(&filo->data->fork[filo->id]);
	}
	pthread_mutex_unlock(&filo->data->stop_mtx);
}
