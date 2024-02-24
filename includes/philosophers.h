/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:59:03 by dan               #+#    #+#             */
/*   Updated: 2024/02/24 12:48:10 by dsylvain         ###   ########.fr       */
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

typedef enum	Fil_state
{
	is_not_eating,
	is_eating
}	Fil_state;

typedef struct s_Philosopher
{
	int				id;
	int				*meals_taken;
	int				*left_fork;
	int				*right_fork;
	int				*fil_state;
	int				*ln_state;
	int				*rn_state;
	bool			has_slept;
	long long int	time_to_die;
	int				*meal_auth;
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
void	update_meal_auth(s_Data **data);

/*   check_input.c                                      :+:      :+:    :+:   */
int	check_input(int argc, char **argv);
int	is_valid_number(char *str);

/*   utils.c                                            :+:      :+:    :+:   */
void	display_error(char *str);
void	free_data(s_Data *data);
void	display_filos(s_Data *data);
void	display_filo(s_Philosopher *filo);

/*   create_and_initialize_data.c                       :+:      :+:    :+:   */
s_Data	*create_and_initialize_data(s_Data *data, char **argv);
s_Data	*create_data(s_Data *data, char **argv);
int		**create_tab(s_Data *data);
s_Data	*initialize_data(s_Data *data, char **argv);
int		get_right_fork_num(int i, int fil_num);
int		get_rn(int	i, int	fil_num);
int		get_ln(int	i, int	fil_num);

#endif
