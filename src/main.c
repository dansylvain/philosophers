/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/02/28 07:18:20 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*filo_routine(void *arg)
{
	t_Data	*filo;
	int *id;
	
	filo = (t_Data *)arg;
	id = (int *)malloc(sizeof(int));
	*id =  *filo->id;	
	ft_printf("%i: hello world\n", *filo->id);
	sleep(1);
	ft_printf("%i: hello world\n", *id);
	// display_filo(filo);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_Data		*data;
	t_Thread_args	**filo;

	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_data_struct(&data, argv) == 0)
		return (display_error("Error\n"), 2);
	int i;
	
	filo = (t_Thread_args **)malloc(sizeof(t_Thread_args) * data->fil_num	);
	if (filo == NULL)
		return (free_data(data, filo), 3);
	i = 0;
	while (i < data->fil_num)
	{
		filo[i] = (t_Thread_args *)malloc(sizeof(t_Thread_args));
		if (filo == NULL)
			return (free_data(data, filo), 4);
		filo[i]->id;
		*data->id = i;
		pthread_create(&data->filo[i], NULL, &filo_routine, data);
		usleep(10000);
		i++;
	}
	i = 0;
	while (i < data->fil_num)
	{
		pthread_join(data->filo[i], NULL);
		i++;
	}
	
	free_data(data, filo);
}