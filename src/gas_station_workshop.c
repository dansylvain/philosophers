/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gas_station_workshop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:35:11 by dan               #+#    #+#             */
/*   Updated: 2024/02/23 15:00:33 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int fuel = 0;
pthread_mutex_t mutex_fuel;
pthread_cond_t enough_fuel;

void	*gasstation(void *arg)
{
	ft_printf("Gas station there\n");
	int i = 0;
	while (i < 5)
	{
		pthread_mutex_lock(&mutex_fuel);
		fuel += 15;
		ft_printf("fuel available: %i\n", fuel);
		pthread_mutex_unlock(&mutex_fuel);
		pthread_cond_signal(&enough_fuel);
		sleep(1);
		i++;
	}
}
void	*car(void *arg)
{
	ft_printf("Car there\n");
	pthread_mutex_lock(&mutex_fuel);
	while (fuel <= 40)
	{
		ft_printf("No fuel available. Waiting.\n");
		pthread_cond_wait(&enough_fuel, &mutex_fuel);
	}
	ft_printf("getting gas!\n");
		fuel -= 40;
	ft_printf("fuel available: %i\n", fuel);
	pthread_mutex_unlock(&mutex_fuel);
}


int	main(int argc, char **argv)
{
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	ft_printf("Welcome to Philosophers\n");
	
	// THREADS STUDY
	
	pthread_t th[2];
	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_cond_init(&enough_fuel, NULL);
	int i;
	i = 0;

	while (i < 2)
	{
		if (i == 0)
		{
			if (pthread_create(&th[i], NULL, &gasstation, NULL) != 0)
				perror("failed too create gasstation thread\n");
			usleep(500);
		}
		else if (i == 1)
		{
			if (pthread_create(&th[i], NULL, &car, NULL) != 0)
				perror("failed too create car thread\n");
			usleep(500);
		}
		i++;
	}
	

	i = 0;
	while (i < 2)
	{
		if (i == 0)
		{
			if (pthread_join(th[i], NULL) != 0)
				perror("failed too create gasstation thread\n");
		}
		else if (i == 1)
		{
			if (pthread_join(th[i], NULL) != 0)
				perror("failed too join car thread\n");
		}
		i++;
	}

	pthread_mutex_destroy(&mutex_fuel);	
	pthread_cond_destroy(&enough_fuel);
	return (0);
}
