/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:45:27 by dan               #+#    #+#             */
/*   Updated: 2024/03/28 02:06:37 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**========================================================================
 *                             PHILOSOPHERS
 *  
 *  
 *  
 *  
 *========================================================================**/
/**========================================================================
 *                           main
 *========================================================================**/
int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_and_initialize_data(&data, argv) == 0)
		return (free_data(data), display_error("Error\n"), 2);
	data = run_threads(data);
	if (data == NULL)
		return (free_data(data), display_error("Error\n"), 3);
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->stop_mtx);
	i = 0;
	while (i < data->fil_nbr)
		pthread_mutex_destroy(&data->fork[i++]);
	free_data(data);
	return (0);
}
