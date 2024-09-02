/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:39:19 by mgering           #+#    #+#             */
/*   Updated: 2024/09/02 17:30:32 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_data(char **argv, t_data *data)
{
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
	if (0 != mutex_handler(&data->start_lock, INIT))
		return (-1);
	alloc_data(data);
	return (0);
}

int	alloc_data(t_data *data)
{
	int	i;

	i = -1;
	data->philos = ft_calloc(data->num_of_philos, sizeof(t_philo));
	if (!data->philos)
		return (-1);
	data->forks = ft_calloc(data->num_of_philos, sizeof(t_fork));
	if (!data->forks)
	{
		free_data(data);
		return (-1);
	}
	while (++i < data->num_of_philos)
	{
		if (0 != mutex_handler(&data->forks[i].fork, INIT))
		{
			free_data(data);
			return (-1);
		}
		data->forks[i].fork_id = i;
	}
	return (0);
}

void	*init_philo(t_data *data, int *i)
{
	while (++*i < data->num_of_philos)
	{
		data->philos[*i].id = *i + 1;
		data->philos[*i].meals_eaten = 0;
		data->philos[*i].meal_time = current_time_ms();
		data->philos[*i].is_dead = false;
		data->philos[*i].full = false;
		if (1 < data->num_of_philos)
			data->philos[*i].left_fork = &data->forks[(*i + 1)
				% data->num_of_philos];
		data->philos[*i].right_fork = &data->forks[*i];
		data->philos[*i].data = data;
		mutex_handler(&data->philos[*i].philo_lock, INIT);
		if (0 != thread_handler(&data->philos[*i], CREATE))
			break ;
	}
	return (NULL);
}
