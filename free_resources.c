/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:39:01 by mgering           #+#    #+#             */
/*   Updated: 2024/08/30 13:56:12 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		if (&data->philos[i] != NULL)
			mutex_handler(&data->philos[i].philo_lock, DESTROY);
		if (&data->forks[i] != NULL)
			mutex_handler(&data->forks[i].fork, DESTROY);
	}
	mutex_handler(&data->print_lock, DESTROY);
	mutex_handler(&data->start_lock, DESTROY);
	if (data->forks != NULL)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos != NULL)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
