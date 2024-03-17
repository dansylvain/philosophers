/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_old.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:59:03 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 07:25:13 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_OLD_H
# define PHILOSOPHERS_OLD_H

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
	eats,
	sleeps,
	thinks,
	dead,
	is_born,
	take_fork,
}	mssg;

typedef enum
{
	eating,
	sleeping,
	thinking
}	fil_state;

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
	pthread_t			bb_th;
	int					*auth_lst;
	pthread_mutex_t		auth_lst_mutex;
	struct t_filo_th	*filos;
}	t_Data;

typedef struct t_filo_th
{
	pthread_t		filo;
	int				id;
	int				meal_count;
	t_Data			*data;
	void			(*say)(long int, int, mssg, pthread_mutex_t *);
	pthread_mutex_t	can_eat_mutex;
	bool			can_eat;
	fil_state		state;
	long int		meal_time;
}	t_filo_th;


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
