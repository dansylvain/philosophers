/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:59:03 by dan               #+#    #+#             */
/*   Updated: 2024/02/24 10:28:34 by dsylvain         ###   ########.fr       */
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
#include <sys/time.h>

typedef struct s_Philosopher
{
	int				id;
	int				*meals_taken;
	int				*left_fork;
	int				*right_fork;
	bool			has_slept;
	long long int	time_to_die;
	int				*	meal_auth;
} s_Philosopher;

typedef struct s_Data
{
	int				fil_num;
	int				**tab;
	int				meal_auth;
	s_Philosopher	**filos;
	
} s_Data;


/*   main.c                                             :+:      :+:    :+:   */
int	main(int argc, char **argv);

/*   check_input.c                                      :+:      :+:    :+:   */
int	check_input(int argc, char **argv);
int	is_valid_number(char *str);

/*   utils.c                                            :+:      :+:    :+:   */
void	display_error(char *str);
void	free_data(s_Data *data);

#endif
