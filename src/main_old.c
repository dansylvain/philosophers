/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 09:34:17 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"
void	suscribe_to_auth_lst(int filo_id, int **auth_lst, int fil_num);

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

t_filo_th	*eat_pasta_and_sleep(t_filo_th *filo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	filo->meal_time = time_to_ms(now);
	filo->say(0, filo->id, eats, &(filo->data->print_mutex));
	filo->state = eating;
	usleep(filo->data->tt_eat);
	filo->say(0, filo->id, sleeps, &(filo->data->print_mutex));
	filo->state = sleeping;
	usleep(filo->data->tt_sleep);
	filo->say(0, filo->id, thinks, &(filo->data->print_mutex));
	filo->state = thinking;
	filo->can_eat = false;
	filo->meal_count++;
	return (filo);	
}

void	suscribe_to_auth_lst(int filo_id, int **auth_lst, int fil_num)
{
	int	i;
	i = 0;
	while(i < fil_num)
		i++;
	printf("%i: enter suscribe_to_auth_lst\n", fil_num);
	(*auth_lst)[i] = filo_id;
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
		pthread_mutex_lock(&filo->data->auth_lst_mutex);
		suscribe_to_auth_lst(filo->id, &(filo->data->auth_lst), filo->id);
		pthread_mutex_unlock(&filo->data->auth_lst_mutex);

		pthread_mutex_lock(&filo->can_eat_mutex);
		if (filo->state == thinking && filo->can_eat == true)
			filo = eat_pasta_and_sleep(filo);
		pthread_mutex_unlock(&filo->can_eat_mutex);
		gettimeofday(&now, NULL);
		time_passed = (time_to_ms(now)) - filo->meal_time ;
	}
	// display filo's death
	filo->say(0, filo->id, dead, &(filo->data->print_mutex));
	
	
	return (NULL);
}

void	display_auth_lst(int *auth_lst, int fil_num)
{
	int i;

	i = 0;
	printf("auth_lst :\n");
	while (i < fil_num)
		printf("%i ", auth_lst[i++]);
	printf("\n");
}

int	get_nxt_fil_to_eat(int **auth_lst)
{
	int i;
	int	nxt_fil_to_eat;
	while ((*auth_lst)[0] == 0)
		usleep(1);
	printf("enter get_nxt_fil_to_eat\n");
	nxt_fil_to_eat = (*auth_lst)[0];
	i = 1;
	while ((*auth_lst)[i])
	{
		(*auth_lst)[i - 1] = (*auth_lst)[i];
		i++;
	}
	return (nxt_fil_to_eat);
}

void	*big_bro(void *arg)
{
	t_Data	*data;
	int		nxt_fil_to_eat;

	usleep(50000);
	data = (t_Data *)arg;
	while(1)
	{
		display_auth_lst(data->auth_lst, data->fil_num);
		pthread_mutex_lock(&data->auth_lst_mutex);
		nxt_fil_to_eat = get_nxt_fil_to_eat(&data->auth_lst);
		pthread_mutex_unlock(&data->auth_lst_mutex);
		pthread_mutex_lock(&data->filos[nxt_fil_to_eat].can_eat_mutex);
		data->filos[nxt_fil_to_eat].can_eat = true;
		pthread_mutex_unlock(&data->filos[nxt_fil_to_eat].can_eat_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("*****\nI am watching you...\n*****\n");
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
	