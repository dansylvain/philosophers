/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:51:59 by dan               #+#    #+#             */
/*   Updated: 2024/03/26 13:00:14 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
void	get_time_now(long int	*time_now);
int		is_valid_number(char *str);

/**========================================================================
 *                           check_input
 *========================================================================**/
int	check_input(int argc, char **argv)
{
	int			i;
	long int	num;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (argv[i])
	{
		num = ft_atoi(argv[i]);
		if (num < 0 || (num == 0 && ft_strlen(argv[i]) > 8))
			return (0);
		if (!is_valid_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

/**========================================================================
 *                           is_valid_number
 *========================================================================**/
int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
