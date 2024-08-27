/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:39:19 by mgering           #+#    #+#             */
/*   Updated: 2024/08/22 17:13:17 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(char **argv, t_data *data)
{
	int	i;

	i = -1;
	data->num_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->num_of_meals = ft_atol(argv[5]);
	else
		data->num_of_meals = -1;
	data->dinner_start = false;
	if (0 != mutex_handler(&data->print_lock, INIT))
		return (-1);
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (-1);
	data->forks = malloc(sizeof(t_fork) * data->num_of_philos);
	if (!data->forks)
	{
		mutex_handler(&data->print_lock, DESTROY);
		free(data->philos);
		return (-1);
	}
	while (++i < data->num_of_philos)
	{
		if (0 != mutex_handler(&data->forks[i].fork, INIT))
		{
			mutex_handler(&data->print_lock, DESTROY);
			while (--i >= 0)
				mutex_handler(&data->forks[i].fork, DESTROY);
			free(data->forks);
			free(data->philos);
			return (-1);
		}
		data->forks[i].fork_id = i;
	}
	return (0);
}
