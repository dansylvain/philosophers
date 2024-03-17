/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 07:24:28 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 07:40:31 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

int	check_input(int argc, char **argv);
int	is_valid_number(char *str);
void	display_error(char *str);
void	free_data(t_Data *data);
int	create_and_initialize_data(t_Data **data, char **argv);


int	main(int argc, char **argv)
{
	t_Data	*data;
	int		i;

	// initial checks
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	
	//data creation and initialization
	if (create_and_initialize_data(&data, argv) == 0)
		return (free_data(data), display_error("Error\n"), 2);
		
	// welcome message
	printf("welcome to the jungle\n");

	//create supervisor thread
	
	// if(pthread_create(&data->bb_th, NULL, big_bro, data) != 0)
	// 	return (free_data(data), display_error("Error\n"), 3);


	// // create philo threads
	// i = 0;
	// while (i < data->fil_num)
	// {
	// 	data->filos[i].id = i;
	// 	if(pthread_create(&data->filos[i].filo, NULL, filo_routine, &data->filos[i]) != 0)
	// 		return (free_data(data), display_error("Error\n"), 3);
	// 	i++;
	// }
	
	
	// // join philo threads
	// i = 0;
	// while (i < data->fil_num)
	// {
	// 	if(pthread_join(data->filos[i].filo, NULL) != 0)
	// 		return (free_data(data), display_error("Error\n"), 4);
	// 	i++;
	// }
	// if(pthread_join(data->bb_th, NULL) != 0)
	// 	return (free_data(data), display_error("Error\n"), 4);
	
	
	// // end application
	// free_data(data);
	// return (0);
	return (0);
}