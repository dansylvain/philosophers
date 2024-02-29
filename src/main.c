/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/02/29 07:49:40 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*filo_routine(void *arg)
{
	t_filo_th	*filo;

	filo = (t_filo_th *)arg;
	display_filo(filo);
	printf("%i: I am a philosopher\n", filo->id);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_Data		*data;
	
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_and_initialize_data_struct(&data, argv) == 0)
		return (display_error("Error\n"), 2);
	printf("welcome to the jungle\n");

	int i;
	i = 0;
	while (i < data->fil_num)
	{
		data->filos[i].id = i;
		pthread_create(&data->filos[i].filo, NULL, filo_routine, &data->filos[i]);
		usleep(500);
		i++;
	}
	i = 0;
	while (i < data->fil_num)
	{
		data->filos[i].id = i;
		pthread_join(data->filos[i].filo, NULL);
		i++;
	}

	free_data(data);
}
