/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:59:02 by mgering           #+#    #+#             */
/*   Updated: 2024/09/02 17:37:42 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philos(t_data *data)
{
	int	i;

	while (read_bool(&data->start_lock, &data->dinner_start))
	{
		i = -1;
		while (++i < data->num_of_philos)
		{
			check_alive(&data->philos[i]);
			usleep(100);
		}
		if (check_philos_full(data))
			write_bool(&data->start_lock, &data->dinner_start, false);
	}
}

bool	check_philos_full(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		if (!read_bool(&data->philos[i].philo_lock, &data->philos[i].full))
			return (false);
		usleep(100);
	}
	return (true);
}

void	check_alive(t_philo *philo)
{
	long	time;

	mutex_handler(&philo->philo_lock, LOCK);
	time = current_time_ms() - philo->meal_time;
	if (time >= philo->data->time_to_die)
	{
		philo_print(philo, DEAD);
		write_bool(&philo->data->start_lock, &philo->data->dinner_start, false);
		philo->is_dead = true;
	}
	mutex_handler(&philo->philo_lock, UNLOCK);
}
