/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:59:09 by mgering           #+#    #+#             */
/*   Updated: 2024/08/27 14:54:34 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	accurate_sleep(long usec)
{
	struct timeval	start;
	struct timeval	end;
	long			elapsed;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < usec)
	{
		gettimeofday(&end, NULL);
		elapsed = (end.tv_sec - start.tv_sec) * 1e6L
			+ (end.tv_usec - start.tv_usec);
	}
	return (elapsed);
}

long	current_time_us(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1e6L) + (time.tv_usec));
}

/* void	cleanup(t_data data)
{
	
} */
