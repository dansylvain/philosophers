/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:47:37 by dan               #+#    #+#             */
/*   Updated: 2024/03/24 19:34:19 by dan              ###   ########.fr       */
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
	int				state;
	int				is_registered;
	int				id;
	int				meals_taken;
	long int		meal_time;
	pthread_t		filo;
	t_data			*data;
	pthread_mutex_t	state_mtx;
}	t_filo;

typedef struct s_Data
{
	pthread_mutex_t	all_filos_live_mtx;
	bool			all_filos_live;
	int				fil_nbr;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_meals;
	int				**auth_tab;
	t_filo			*filo;
	pthread_t		coor;
	pthread_mutex_t	auth_tab_mtx;
	pthread_mutex_t	auth_tab_queue_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	*fork;
}	t_data;
