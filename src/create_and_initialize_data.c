/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_initialize_data.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:39:09 by dsylvain          #+#    #+#             */
/*   Updated: 2024/02/24 12:56:49 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**========================================================================
 *                             create_and_initialize_data
 *  data are created (malloc'd) and initialized here.
 *  refer to philosophers.h for data structures
 *  each thread receives a struct refering to main data
 *  
 *========================================================================**/
/**========================================================================
 *                           create_and_initialize_data
 *========================================================================**/
s_Data	*create_and_initialize_data(s_Data *data, char **argv)
{
	int	i;

	data = create_data(data, argv);
	if (data == NULL)
		return (NULL);
	data->tab = create_tab(data);
	if (data->tab == NULL)
		return (NULL);
	data = initialize_data(data, argv);
	return (data);
}

/**========================================================================
 *                           create_data
 *========================================================================**/
s_Data	*create_data(s_Data *data, char **argv)
{
	int	i;

	data = (s_Data *)ft_calloc(1, sizeof(s_Data));
	if (data == NULL)
		return (NULL);
	data->fil_num = ft_atoi(argv[1]);
	data->filos = (s_Philosopher **)ft_calloc(data->fil_num + 1,
			sizeof(s_Philosopher *));
	if (data->filos == NULL)
		return (NULL);
	i = 0;
	while (i < data->fil_num)
	{
		data->filos[i] = (s_Philosopher *)ft_calloc(1, sizeof(s_Philosopher));
		if (data->filos[i] == NULL)
			return (NULL);
		i++;
	}
	data->filos[i] = NULL;
	return (data);
}

/**========================================================================
 *                           create_tab
 *========================================================================**/
int	**create_tab(s_Data *data)
{
	int	i;

	data->tab = (int **)ft_calloc(4, sizeof(int *));
	if (data->tab == NULL)
		return (NULL);
	i = 0;
	while (i < data->fil_num)
	{
		data->tab[i] = (int *)ft_calloc(data->fil_num + 1, sizeof(int));
		if (data->tab[i] == NULL)
			return (NULL);
		data->tab[data->fil_num] = NULL;
		i++;
	}
	data->tab[i] = NULL;
	return (data->tab);
}

/**========================================================================
 *                           initialize_data
 *	data->tab[0] : forks. 1 = unused, 0 = in use.
 *	data->tab[1] : filos meals state. starts at 0.
 *========================================================================**/
s_Data	*initialize_data(s_Data *data, char **argv)
{
	int	i;

	i = 0;
	while (i < data->fil_num)
	{
		data->tab[0][i] = 1;
		data->tab[1][i] = 0;
		data->tab[2][i++] = 0;
	}
	update_meal_auth(&data);
	i = 0;
	while (i < data->fil_num)
	{
		data->filos[i]->id = i;
		data->filos[i]->meals_taken = &data->tab[1][i];
		data->filos[i]->time_to_die = ft_atoi(argv[2]);
		data->filos[i]->meal_auth = &data->tab[1][i];
		data->filos[i]->left_fork = &data->tab[0][i];
		data->filos[i]->right_fork = &data->tab[0][get_rn(i, data->fil_num)];
		data->filos[i]->fil_state = &data->tab[2][i];
		data->filos[i]->rn_state = &data->tab[2][get_rn(i, data->fil_num)];
		data->filos[i]->ln_state = &data->tab[2][get_ln(i, data->fil_num)];
		data->filos[i++]->has_slept = true;
	}
	return (data);
}

int	get_ln(int i, int fil_num)
{
	int	ln_num;

	ln_num = i - 1;
	if (i == 0)
		ln_num = fil_num - 1;
	return (ln_num);
}

int	get_rn(int i, int fil_num)
{
	int	rn_num;

	rn_num = i + 1;
	if (i == fil_num - 1)
		rn_num = 0;
	return (rn_num);
}
