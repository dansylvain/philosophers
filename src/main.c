/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:54:14 by dan               #+#    #+#             */
/*   Updated: 2024/02/25 10:41:47 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



int main(int argc, char **argv)
{
	t_Data	*data;

	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	if (create_data_struct(&data, argv) == 0)
		return (display_error("Error\n"), 1);
	
	free_data(data);
}