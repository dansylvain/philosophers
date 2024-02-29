/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:59:03 by dan               #+#    #+#             */
/*   Updated: 2024/02/29 06:54:45 by dsylvain         ###   ########.fr       */
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


typedef struct
{
	int			fil_num;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			max_meals;
	int			*fork;
}	t_Data;

typedef struct
{
	pthread_t	filo;
    int			id;
	int			meal_count;
    t_Data		*data;
}	t_Thread_args;

/*   main.c                                             :+:      :+:    :+:   */
int main(int argc, char **argv);

/*   check_input.c                                      :+:      :+:    :+:   */
int	check_input(int argc, char **argv);
int	is_valid_number(char *str);

/*   utils.c                                            :+:      :+:    :+:   */
void	display_error(char *str);

#endif
