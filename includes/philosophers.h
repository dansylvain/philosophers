/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:59:03 by dan               #+#    #+#             */
/*   Updated: 2024/03/15 17:04:05 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include <pthread.h>
# include <sys/time.h>

typedef enum
{
	is_born,
	take_fork,
	eats,
	sleeps,
	thinks,
	dead
}	mssg;

typedef struct t_filo_th	t_filo_th;

typedef struct s_Data
{
	pthread_mutex_t 	print_mutex;
	int					fil_num;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					max_meals;
	pthread_mutex_t		*forks;
	pthread_t			supervisor;
	struct t_filo_th	*filos;
}	t_Data;

typedef struct t_filo_th
{
	pthread_t	filo;
	int			id;
	int			meal_count;
	t_Data		*data;
	void		(*say)(long int, int, mssg, pthread_mutex_t *);
}	t_filo_th;


/* 
timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died

take_fork,
	eats,
	sleeps,
	thinks,
	dead
}	mssg;
 */




/*   main.c                                             :+:      :+:    :+:   */
int		main(int argc, char **argv);

/*   check_input.c                                      :+:      :+:    :+:   */
int		check_input(int argc, char **argv);
int		is_valid_number(char *str);

/*   utils.c                                            :+:      :+:    :+:   */
void	display_error(char *str);
int		create_and_initialize_data_struct(t_Data **data, char **argv);
void	free_data(t_Data *data);
void	display_filo(t_filo_th *filo);

#endif
