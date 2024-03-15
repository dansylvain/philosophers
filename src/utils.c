/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:07 by dan               #+#    #+#             */
/*   Updated: 2024/03/15 06:06:18 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**========================================================================
 *                           display_error
 *========================================================================**/
void	display_error(char *str)
{
	if (write (2, str, ft_strlen(str)) == -1)
		perror("display_error");
}

/**========================================================================
 *                           create_data_struct
 *! every var initialized except (*data)->filos[i].id (init at th creation)
 *========================================================================**/
int	create_and_initialize_data_struct(t_Data **data, char **argv)
{
	int			i;

	*data = (t_Data *)ft_calloc(1, sizeof(t_Data));
	if (!data)
		return (0);
	if (pthread_mutex_init(&((*data)->print_mutex), NULL) != 0)
		return (free(*data), 0);
	(*data)->fil_num = ft_atoi(argv[1]);
	(*data)->tt_die = ft_atoi(argv[2]);
	(*data)->tt_eat = ft_atoi(argv[3]);
	(*data)->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*data)->max_meals = ft_atoi(argv[5]);
	(*data)->forks = (pthread_mutex_t *)ft_calloc((*data)->fil_num, sizeof(pthread_mutex_t));
	(*data)->filos = (t_filo_th *)ft_calloc((*data)->fil_num, sizeof(t_filo_th));
	if (!(*data)->forks || !(*data)->filos)
		return (0);
	i = 0;
	while (i < (*data)->fil_num)
	{
	    pthread_mutex_init(&((*data)->forks[i]), NULL);
		(*data)->filos[i].meal_count = 0;
		(*data)->filos[i].data = *data;
		i++;
	}
	return (1);
}

/**========================================================================
 *                           free_data
 *========================================================================**/
void	free_data(t_Data *data)
{
	free(data->forks);
	free(data->filos);
	free(data);
}

void	display_filo(t_filo_th *filo)
{
	printf("id: %i\n", filo->id);
	printf("meal_count: %i\n", filo->meal_count);
	printf("data->fil_num: %i\n", filo->data->fil_num);
	printf("data->tt_die: %i\n", filo->data->tt_die);
	printf("data->tt_eat: %i\n", filo->data->tt_eat);
	printf("data->tt_sleep: %i\n", filo->data->tt_sleep);
	if (filo->data->max_meals)
		printf("data->max_meals: %i\n", filo->data->max_meals);
}
