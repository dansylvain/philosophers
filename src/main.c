/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/03/15 06:22:26 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*filo_routine(void *arg)
{
	t_filo_th	*filo;
	struct timeval	start;
	struct timeval	now;
	long	int time_passed;
	char *message;

	filo = (t_filo_th *)arg;
	time_passed = 0;
	gettimeofday(&start, NULL);
	pthread_mutex_lock(&filo->data->print_mutex);
	printf("%i: time now: %ld\n", filo->id, start.tv_sec * 1000000 + start.tv_usec);
	pthread_mutex_unlock(&filo->data->print_mutex);
	while (time_passed < filo->data->tt_die * 1000000)
	{
	gettimeofday(&now, NULL);
	time_passed = (now.tv_sec * 1000000 + now.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	}
	pthread_mutex_lock(&filo->data->print_mutex);
	printf("filo %i died\n", filo->id);
	pthread_mutex_unlock(&filo->data->print_mutex);	
	// display_filo(filo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_Data	*data;
	int		i;

	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_and_initialize_data_struct(&data, argv) == 0)
		return (display_error("Error\n"), 2);
	printf("welcome to the jungle\n");
	i = 0;
	while (i < data->fil_num)
	{
		data->filos[i].id = i;
		pthread_create(&data->filos[i].filo, NULL, filo_routine, &data->filos[i]);
		i++;
	}
	i = 0;
	while (i < data->fil_num)
	{
		pthread_join(data->filos[i].filo, NULL);
		i++;
	}
	free_data(data);
}
	