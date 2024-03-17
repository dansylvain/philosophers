/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 09:57:02 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <pthread.h>

int		check_input(int argc, char **argv);
void	free_data(t_Data *data);
void	display_error(char *str);
int		create_and_initialize_data(t_Data **data, char **argv);

void	*filo_routine(void *arg)
{
	t_filo *filo;

	filo = (t_filo *)arg;
	pthread_mutex_lock(&filo->data->print_mutex);
	printf("%i: hello!\n", filo->id);
	pthread_mutex_unlock(&filo->data->print_mutex);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_Data	*data;
	int		i;
	
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_and_initialize_data(&data, argv) == 0)
		return (free_data(data), display_error("Error\n"), 2);
	
	printf("welcome to the jungle\n");
	// printf("%i, %i, %i, %i, %i\n", data->fil_nbr, data->tt_die, data->tt_eat, data->tt_sleep, data->max_meals);
	
	i = 0;
	while (i < data->fil_nbr)
	{
		data->filo[i].id = i;
		if(pthread_create(&data->filo[i].filo, NULL, filo_routine, &data->filo[i]) != 0)
			return (free_data(data), display_error("Error\n"), 3);
		i++;
	}
	
	i = 0;
	while (i < data->fil_nbr)
	{
		if(pthread_join(data->filo[i].filo, NULL) != 0)
			return (free_data(data), display_error("Error\n"), 4);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free_data(data);
	return (0);
}