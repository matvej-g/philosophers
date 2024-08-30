/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:44:12 by mgering           #+#    #+#             */
/*   Updated: 2024/08/29 14:51:57 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(int ret, const char *err_msg)
{
	if (0 != ret)
		printf("%s failed with error code %d\n", err_msg, ret);
	return (ret);
}

int	mutex_handler(pthread_mutex_t *mutex, t_operation operation)
{
	int	ret;

	ret = 0;
	if (operation == INIT)
		ret = error_msg(pthread_mutex_init(mutex, NULL), "mutex INIT");
	else if (operation == DESTROY)
		ret = error_msg(pthread_mutex_destroy(mutex), "mutex DESTROY");
	else if (operation == LOCK)
		ret = error_msg(pthread_mutex_lock(mutex), "mutex LOCK");
	else if (operation == UNLOCK)
		ret = error_msg(pthread_mutex_unlock(mutex), "mutex UNLOCK");
	return (ret);
}

int	thread_handler(t_philo *philo, t_operation operation)
{
	int	ret;

	ret = 0;
	if (operation == CREATE)
		ret = error_msg(pthread_create(&philo->thread,
					NULL, philo_routine, philo), "pthread CREATE");
	else if (operation == DETACH)
		ret = error_msg(pthread_detach(philo->thread), "pthread DETACH");
	else if (operation == JOIN)
		ret = error_msg(pthread_join(philo->thread, NULL), "pthread JOIN");
	return (ret);
}
