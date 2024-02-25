/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:35:11 by dan               #+#    #+#             */
/*   Updated: 2024/02/24 16:15:37 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_meal_auth(s_Data **data)
{
	int	i;
	
	i = 0;
	while ((*data)->tab[1][i])
	{
		if ((*data)->tab[1][i] > (*data)->meal_auth)
			(*data)->meal_auth = (*data)->tab[1][i];
		i++;
	}	
}
void	*filo_routine(void *arg)
{
	s_Philosopher *filo;

	filo = (s_Philosopher *)arg;
	display_filo(filo);
	
	if (*filo->meal_auth == *filo->meals_taken && *filo->left_fork && *filo->right_fork)
		ft_printf("%i: TIME TO EAT!!!\n", filo->id);

	
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				i;
	s_Data			*data;
	
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);	
	data = create_and_initialize_data(data, argv);
	if (data == NULL)
		return (free_data(data), display_error("Error\n"), 2);

	pthread_t	filo[data->fil_num];
	i = 0;
	while (i < data->fil_num)
	{
		if(pthread_create(&filo[i], NULL, &filo_routine, data->filos[i]) != 0)
			return (free_data(data), display_error("Error\n"), 3);
		usleep(500);
		i++;
	}
	i = 0;
	while (i < data->fil_num)
	{
		if(pthread_join(filo[i], NULL) != 0)
			return (free_data(data), display_error("Error\n"), 3);
		i++;
	}
	// pthread_create();
	free_data(data);
}

