/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filo_routine.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:28:39 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 13:37:57 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILO_ROUTINE_H
# define FILO_ROUTINE_H

# include "philosophers.h"
# include <sys/time.h>
# include <unistd.h>

void	xpress_mssg(t_filo *filo, t_mssg mssg);
long	time_to_ms(struct timeval time_struct);
void	get_time_now(long int	*time_now);
int		time_is_up(t_filo *filo);
void	check_death_condition(t_filo *filo);
void	get_forks(t_filo *filo);
int		eat_and_sleep(t_filo *filo);

#endif