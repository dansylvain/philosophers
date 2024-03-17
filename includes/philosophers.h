/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 07:24:57 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 08:33:37 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>

typedef struct s_Data t_Data;

typedef struct s_filo
{
	int	id;
	pthread_t	filo;
	t_Data		*data;
	
} t_filo;

typedef struct s_Data
{
	int	fil_nbr;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	max_meals;
	t_filo *filo;
	pthread_mutex_t stdout_mtx;
}	t_Data;

#endif