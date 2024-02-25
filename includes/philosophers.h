/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:59:03 by dan               #+#    #+#             */
/*   Updated: 2024/02/25 10:17:36 by dan              ###   ########.fr       */
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

typedef struct s_Data
{

}	t_Data;

/*   main.c                                             :+:      :+:    :+:   */
int main(int argc, char **argv);

/*   check_input.c                                      :+:      :+:    :+:   */
int	check_input(int argc, char **argv);
int	is_valid_number(char *str);

/*   utils.c                                            :+:      :+:    :+:   */
void	display_error(char *str);
void	free_data(t_Data *data);

#endif
