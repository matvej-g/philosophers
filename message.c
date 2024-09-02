/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:58:45 by mgering           #+#    #+#             */
/*   Updated: 2024/09/02 17:37:41 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_print(t_philo *philo, t_print msg)
{
	long	time;
	t_data	*data;

	data = (t_data *)philo->data;
	time = current_time_ms();
	time -= read_time(&philo->data->start_lock, &philo->start_time);
	mutex_handler(&data->print_lock, LOCK);
	if (!read_bool(&philo->data->start_lock, &philo->data->dinner_start))
	{
		mutex_handler(&data->print_lock, UNLOCK);
		return (0);
	}
	if (msg == L_FORK || msg == R_FORK)
		printf(BL"%ld %d has taken a fork\n"RST, time, philo->id);
	else if (msg == EAT)
		printf(YEL"%ld %d is eating\n"RST, time, philo->id);
	else if (msg == SLEEP)
		printf(GR"%ld %d is sleeping\n"RST, time, philo->id);
	else if (msg == THINK)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (msg == DEAD)
		printf(RED"%ld %d died\n"RST, time, philo->id);
	mutex_handler(&data->print_lock, UNLOCK);
	return (0);
}
