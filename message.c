/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:58:45 by mgering           #+#    #+#             */
/*   Updated: 2024/08/30 13:32:28 by mgering          ###   ########.fr       */
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
	if (!read_bool(&philo->data->start_lock, &philo->data->dinner_start))
		return (0);
	if (0 != mutex_handler(&data->print_lock, LOCK))
		return (-1);
	if (msg == L_FORK)
		printf(BL"%ld %d has taken a fork\n"RST, time, philo->id);
	else if (msg == R_FORK)
		printf(CY"%ld %d has taken a fork\n"RST, time, philo->id);
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
