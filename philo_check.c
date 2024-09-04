/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:59:02 by mgering           #+#    #+#             */
/*   Updated: 2024/09/04 13:52:30 by mgering          ###   ########.fr       */
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
		if (!read_bool(&data->philos[i].bool_lock, &data->philos[i].full))
			return (false);
		usleep(100);
	}
	return (true);
}

void	check_alive(t_philo *philo)
{
	long	time;

	time = current_time_ms() - read_time(&philo->philo_lock, &philo->meal_time);
	if (time >= philo->data->time_to_die)
	{
		philo_print(philo, DEAD);
		write_bool(&philo->data->start_lock, &philo->data->dinner_start, false);
	}
	else if (time > (philo->data->time_to_eat + 5))
		write_bool(&philo->bool_lock, &philo->can_eat, true);
}
