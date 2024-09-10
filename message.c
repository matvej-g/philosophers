/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:58:45 by mgering           #+#    #+#             */
/*   Updated: 2024/09/10 14:47:45 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_print(t_philo *philo, t_print msg)
{
	long	time;
	t_data	*data;

	data = (t_data *)philo->data;
	mutex_handler(&data->print_lock, LOCK);
	if (!read_bool(&philo->data->start_lock, &philo->data->dinner_start))
	{
		mutex_handler(&data->print_lock, UNLOCK);
		return (-1);
	}
	time = current_time_ms();
	time -= read_time(&philo->data->start_lock, &philo->data->start_time);
	if (msg == FORK)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (msg == EAT)
		printf("%ld %d is eating\n", time, philo->id);
	else if (msg == SLEEP)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (msg == THINK)
		printf("%ld %d is thinking\n", time, philo->id);
	mutex_handler(&data->print_lock, UNLOCK);
	return (0);
}
