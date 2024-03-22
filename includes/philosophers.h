/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:47:37 by dan               #+#    #+#             */
/*   Updated: 2024/03/22 10:31:44 by dan              ###   ########.fr       */
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
	got_born,
}	t_mssg;

typedef struct s_Data	t_data;

typedef struct s_filo
{
	bool			is_signed_in;
	bool			can_eat;
	bool			is_subscribed;
	pthread_mutex_t	is_subscribed_mtx;
	pthread_mutex_t	can_eat_mtx;
	int				id;
	long int		meal_time;
	pthread_t		filo;
	t_data			*data;
}	t_filo;

typedef struct s_Data
{
	int				fil_nbr;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_meals;
	int				*auth_tab;
	t_filo			*filo;
	pthread_t		coor;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	auth_tab_mtx;
	pthread_mutex_t	*fork;
}	t_data;
