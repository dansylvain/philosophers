/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 05:40:59 by dan              ###   ########.fr       */
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

t_filo_th	*sleep_for_a_while(t_filo_th *filo)
{
	filo->say(0, filo->id, sleeps, &(filo->data->print_mutex));
	pthread_mutex_lock(&filo->can_eat_mutex);
	usleep(filo->data->tt_sleep);
	pthread_mutex_unlock(&filo->can_eat_mutex);
	filo->can_eat = true;
	return (filo);
}

t_filo_th	*eat_pasta(t_filo_th *filo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	filo->meal_time = time_to_ms(now);
	filo->say(0, filo->id, eats, &(filo->data->print_mutex));
	pthread_mutex_lock(&filo->can_eat_mutex);
	filo->can_eat = false;
	pthread_mutex_unlock(&filo->can_eat_mutex);
	usleep(filo->data->tt_eat);
	filo->meal_count++;
	return (filo);	
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
		pthread_mutex_lock(&filo->can_eat_mutex);
		if (filo->state == thinking && filo->can_eat == true)
			filo = eat_pasta(filo);
		pthread_mutex_unlock(&filo->can_eat_mutex);
		if (filo->state == sleeping)
			filo = sleep_for_a_while(filo);
		gettimeofday(&now, NULL);
		time_passed = (time_to_ms(now)) - filo->meal_time ;
	}
	filo->say(0, filo->id, dead, &(filo->data->print_mutex));
	
	// display filo's death
	
	return (NULL);
}

void	*big_bro(void *arg)
{
	t_Data	*data;
	
	data = (t_Data *)arg;
	while(1)
	{
		sleep(1);
		pthread_mutex_lock(&data->filos[1].can_eat_mutex);
		data->filos[1].can_eat = true;
		pthread_mutex_unlock(&data->filos[1].can_eat_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("I am watching you...\n%i\n", data->tt_die);
		pthread_mutex_unlock(&data->print_mutex);	
	}
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

	//create supervisor thread
	
	if(pthread_create(&data->bb_th, NULL, big_bro, data) != 0)
		return (free_data(data), display_error("Error\n"), 3);


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
	if(pthread_join(data->bb_th, NULL) != 0)
		return (free_data(data), display_error("Error\n"), 4);
	
	
	// end application
	free_data(data);
	return (0);
}
	