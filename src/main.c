/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/03/15 18:01:44 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

/**========================================================================
 *                           time_to_ms 
 *========================================================================**/
long	time_to_ms(struct timeval time_struct)
{
	return (time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000);
}

/**========================================================================
 *                           xpress_mssg 
 *========================================================================**/
void	xpress_mssg(long int t, int fil, mssg mssg, pthread_mutex_t *mut)
{
	char *mssg_str;
	struct timeval	now;

	if (mssg == take_fork)
		mssg_str = "has taken a fork";
	if (mssg == eats)
		mssg_str = "is eating";
	if (mssg == sleeps)
		mssg_str = "is sleeping";
	if (mssg == thinks)
		mssg_str = "is thinking";
	if (mssg == dead)
		mssg_str = "died";
	if (mssg == is_born)
		mssg_str = "is born";	
	pthread_mutex_lock(mut);
	gettimeofday(&now, NULL);
	if (t == 0)
		t = time_to_ms(now);
	printf("%li %i %s\n", t, fil, mssg_str);
	pthread_mutex_unlock(mut);
}

/**========================================================================
 *                           filo_routine 
 *========================================================================**/
void	*filo_routine(void *arg)
{
	t_filo_th		*filo;
	struct timeval	start;
	struct timeval	now;
	long int		time_passed;

	// initialize / reassign variables/structs
	filo = (t_filo_th *)arg;
	time_passed = 0;
	
	// display starting time	
	filo->say(0, filo->id, is_born, &(filo->data->print_mutex));

	// live or die loop 
	// reinitialise time_passed to 0 at each meal start
	gettimeofday(&start, NULL);
	while (time_passed < filo->data->tt_die)
	{
	gettimeofday(&now, NULL);
	time_passed = (time_to_ms(now)) - (time_to_ms(start)) ;
	}
	filo->say(0, filo->id, dead, &(filo->data->print_mutex));
	
	// display filo's death
	
	return (NULL);
}

/**========================================================================
 *                           main 
 *========================================================================**/
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
	