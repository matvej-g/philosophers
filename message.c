/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:58:45 by mgering           #+#    #+#             */
/*   Updated: 2024/08/27 14:54:51 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_print(t_philo *philo, t_print msg)
{
	t_data	*data;

	data = (t_data *)philo->data;
	data->current_time = current_time_us();
	data->current_time -= data->dinner_time_start;
	if (0 != mutex_handler(&data->print_lock, LOCK))
		return (-1);
	if (msg == L_FORK)
		printf(BL"%ld %d has taken a fork\n"RST, data->current_time, philo->id);
	else if (msg == R_FORK)
		printf(CY"%ld %d has taken a fork\n"RST, data->current_time, philo->id);
	else if (msg == EAT)
		printf(YEL"%ld %d is eating\n"RST, data->current_time, philo->id);
	else if (msg == SLEEP)
		printf(GR"%ld %d is sleeping\n"RST, data->current_time, philo->id);
	else if (msg == THINK)
		printf("%ld %d is thinking\n", data->current_time, philo->id);
	else if (msg == DEAD)
		printf(RED"%ld %d died\n"RST, data->current_time, philo->id);
	mutex_handler(&data->print_lock, UNLOCK);
	return (0);
}
