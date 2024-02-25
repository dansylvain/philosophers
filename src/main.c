/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/02/25 10:17:12 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_data_struct(t_Data **data, char **argv)
{
	return (1);
}

void	*filo_routine(void *arg)
{
	t_Data *filo;
	
	filo = (t_Data *)arg;
	ft_printf("%i: hello world\n", *filo->id);
	
	free(filo->id);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_Data	*data;
	pthread_t *filo;
	bool	*fork;

	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_data_struct(&data, argv) == 0)
		return (display_error("Error\n"), 1);
	
	
}