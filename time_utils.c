/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:59:09 by mgering           #+#    #+#             */
/*   Updated: 2024/09/10 13:11:23 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	accurate_sleep(long msec)
{
	long	start;

	start = current_time_ms();
	while ((current_time_ms() - start) < msec)
		usleep(500);
}

long	current_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1e3L) + (time.tv_usec / 1e3L));
}
