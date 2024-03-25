/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:47:37 by dan               #+#    #+#             */
/*   Updated: 2024/03/25 18:15:49 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>

typedef enum mssg
{
	eating,
	sleeping,
	thinking,
	dead,
	take_fork,
	got_born
}	t_mssg;

typedef struct s_data	t_data;

typedef struct s_filo
{
	bool			lfork_taken;
	bool			rfork_taken;
	t_mssg			state;
	int				id;
	int				max_meals;
	int				meals_taken;
	long int		meal_time;
	pthread_t		filo;
	t_data			*data;
}	t_filo;

typedef struct s_data
{
	bool			stop;
	int				fil_nbr;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_meals;
	t_filo			*filo;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	*fork;
}	t_data;
