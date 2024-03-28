/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:28:56 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 13:40:29 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include "philosophers.h"
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s);
long	time_to_ms(struct timeval time_struct);
void	*filo_rtn(void *arg);

#endif