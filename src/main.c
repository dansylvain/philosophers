/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/02/29 06:49:30 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*filo_routine(void *arg)
{

}

int main(int argc, char **argv)
{
	t_Data		*data;
	t_Thread_args	**filo;

	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_data_struct(&data, argv) == 0)
		return (display_error("Error\n"), 2);
	
}