/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/02/25 11:05:42 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*filo_routine(void *arg)
{
	t_Data	*filo;

	filo = (t_Data *)arg;
	ft_printf("%i: hello world\n", *filo->id);
	display_filo(filo);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_Data	*data;
	pthread_t	*filo;

	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_data_struct(&data, argv) == 0)
		return (display_error("Error\n"), 2);
	int i;
	
	i = 0;
	while (i < data->fil_num)
	{
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
	
	

	free_data(data);
}