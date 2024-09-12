/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:59:02 by mgering           #+#    #+#             */
/*   Updated: 2024/09/12 15:01:41 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_philos_full(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->num_of_philos
		&& read_bool(&data->start_lock, &data->dinner_start))
	{
		if (!read_bool(&data->philos[i].bool_lock, &data->philos[i].full))
			i = -1;
		usleep(10);
	}
	write_bool(&data->start_lock, &data->dinner_start, false);
	return (NULL);
}

void	*check_philos_alive(void *arg)
{
	t_data	*data;
	long	time;
	int		i;

	data = (t_data *)arg;
	while (read_bool(&data->start_lock, &data->dinner_start))
	{
		i = -1;
		while (++i < data->num_of_philos)
		{
			time = (current_time_ms()
					- read_time(&data->philos[i].philo_lock,
						&data->philos[i].meal_time));
			if (time >= data->time_to_die)
				stop_dinner(data, &i, &time);
			else if (time > (data->time_to_eat + 5))
				write_bool(&data->philos[i].bool_lock,
					&data->philos[i].can_eat, true);
			usleep(10);
		}
	}
	return (NULL);
}

void	*stop_dinner(t_data *data, int *i, long *time)
{
	pthread_mutex_lock(&data->print_lock);
	if (!read_bool(&data->start_lock, &data->dinner_start))
	{
		pthread_mutex_unlock(&data->print_lock);
		return (NULL);
	}
	printf(RED"%ld %d died\n"RST, *time, data->philos[*i].id);
	write_bool(&data->start_lock, &data->dinner_start, false);
	pthread_mutex_unlock(&data->print_lock);
	return (NULL);
}
