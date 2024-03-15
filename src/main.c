/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/03/15 09:31:14 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"
long	time_to_ms(struct timeval time_struct)
{
	return (time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000);
}


void	xpress_mssg()
{

}

void	*filo_routine(void *arg)
{
	t_filo_th		*filo;
	struct timeval	start;
	struct timeval	now;
	long int		time_passed;

	// initialize / reassign variables/structs
	filo = (t_filo_th *)arg;
	time_passed = 0;
	gettimeofday(&start, NULL);
	
	// display starting time
	pthread_mutex_lock(&filo->data->print_mutex);
	printf("%i: time now: %ld\n", filo->id, time_to_ms(start)) ;
	pthread_mutex_unlock(&filo->data->print_mutex);
	
	// live or die loop 
	// reinitialise time_passed to 0 at each meal start
	while (time_passed < filo->data->tt_die)
	{
	gettimeofday(&now, NULL);
	time_passed = (time_to_ms(now)) - (time_to_ms(start)) ;
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

	// initial checks
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	
	//data creation and initialization
	if (create_and_initialize_data_struct(&data, argv) == 0)
		return (free_data(data), display_error("Error\n"), 2);
		
	// welcome message
	printf("welcome to the jungle\n");
	
	
	// create philo threads
	i = 0;
	while (i < data->fil_num)
	{
		data->filos[i].id = i;
		if(pthread_create(&data->filos[i].filo, NULL, filo_routine, &data->filos[i]) != 0)
			return (free_data(data), display_error("Error\n"), 3);
		i++;
	}
	

	// join philo threads
	i = 0;
	while (i < data->fil_num)
	{
		if(pthread_join(data->filos[i].filo, NULL) != 0)
			return (free_data(data), display_error("Error\n"), 4);
		i++;
	}
	
	// end application
	free_data(data);
	return (0);
}
	