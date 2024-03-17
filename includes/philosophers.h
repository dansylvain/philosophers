/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:47:37 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 08:53:34 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	(*data)->fil_num = ft_atoi(argv[1]);
	(*data)->tt_die = ft_atoi(argv[2]);
	(*data)->tt_eat = ft_atoi(argv[3]);
	(*data)->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*data)->max_meals = ft_atoi(argv[5]); */

typedef struct s_Data
{
	int	fil_nbr;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	max_meals;	
} t_Data;