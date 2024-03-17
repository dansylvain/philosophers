/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 10:24:16 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <pthread.h>
# include <sys/time.h>

int		check_input(int argc, char **argv);
void	free_data(t_Data *data);
void	display_error(char *str);
int		create_and_initialize_data(t_Data **data, char **argv);
t_Data	*run_threads(t_Data *data);
void	xpress_mssg(t_filo *filo, mssg mssg);



void	*filo_routine(void *arg)
{
	t_filo *filo;

	filo = (t_filo *)arg;
	// pthread_mutex_lock(&filo->data->print_mutex);
	xpress_mssg(filo, eating);
	// printf("%i: hello!\n", filo->id);
	// pthread_mutex_unlock(&filo->data->print_mutex);
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
	data = run_threads(data);
	if (data == NULL)
		return (free_data(data), display_error("Error\n"), 3);
	
	pthread_mutex_destroy(&data->print_mutex);
	free_data(data);
	return (0);
}

t_Data *run_threads(t_Data *data)
{
	int	i;
	
	i = 0;
	while (i < data->fil_nbr)
	{
		data->filo[i].id = i;
		if(pthread_create(&data->filo[i++].filo, NULL, filo_routine, &data->filo[i]) != 0)
			return (NULL);
	}
	i = 0;
	while (i < data->fil_nbr)
	{
		if(pthread_join(data->filo[i++].filo, NULL) != 0)
			return (NULL);
	}
	return (data);	
}