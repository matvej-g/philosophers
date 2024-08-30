/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:43:20 by mgering           #+#    #+#             */
/*   Updated: 2024/08/30 12:26:39 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	read_bool(pthread_mutex_t *mtx, bool *dst)
{
	bool	result;

	mutex_handler(mtx, LOCK);
	result = *dst;
	mutex_handler(mtx, UNLOCK);
	return (result);
}

void	write_bool(pthread_mutex_t *mtx, bool *dst, bool src)
{
	mutex_handler(mtx, LOCK);
	*dst = src;
	mutex_handler(mtx, UNLOCK);
}

long	read_time(pthread_mutex_t *mtx, long *dst)
{
	long	result;

	mutex_handler(mtx, LOCK);
	result = *dst;
	mutex_handler(mtx, UNLOCK);
	return (result);
}

void	write_long(pthread_mutex_t *mtx, long *dst, long src)
{
	mutex_handler(mtx, LOCK);
	*dst = src;
	mutex_handler(mtx, UNLOCK);
}
