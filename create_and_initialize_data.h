/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_initialize_data.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:28:35 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 13:40:18 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_AND_INITIALIZE_DATA_H
# define CREATE_AND_INITIALIZE_DATA_H

# include "philosophers.h"
# include <limits.h>
# include <sys/time.h>

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);
int		alloc_memory_for_data(t_data **data, char **argv);
long	time_to_ms(struct timeval time_struct);
void	add_argv_data(t_data **data, char **argv);
int		initialize_mutex(t_data **data);
void	initialize_filos(t_data **data);

#endif