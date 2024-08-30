/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:59:09 by mgering           #+#    #+#             */
/*   Updated: 2024/08/29 14:51:49 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	accurate_sleep(long msec)
{
	struct timeval	start;
	struct timeval	end;
	long			elapsed;

	msec *= 1000;
	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < msec)
	{
		gettimeofday(&end, NULL);
		elapsed = (end.tv_sec - start.tv_sec) * 1e6L
			+ (end.tv_usec - start.tv_usec);
	}
	return (elapsed);
}

long	current_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1e3L) + (time.tv_usec / 1e3L));
}
