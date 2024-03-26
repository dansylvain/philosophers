/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:28:26 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 13:39:33 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_INPUT_H
# define CHECK_INPUT_H

# include <stddef.h>

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
int		is_valid_number(char *str);

#endif