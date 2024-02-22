/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:35:11 by dan               #+#    #+#             */
/*   Updated: 2024/02/22 11:55:55 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	if (check_input(argc, argv) == 0)
		return (display_error("Error\n"), 1);
	ft_printf("Welcome to Philosophers\n");
	return (0);
}