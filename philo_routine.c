/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:57:40 by mgering           #+#    #+#             */
/*   Updated: 2024/09/03 16:20:09 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (wait_all_philos(philo))
		usleep(10);
	write_long(&philo->philo_lock, &philo->start_time, current_time_ms());
	write_long(&philo->philo_lock, &philo->meal_time, current_time_ms());
	if (philo->data->num_of_philos == 1)
	{
		one_routine(philo);
		return (NULL);
	}
	else if ((philo->id + 1) % 2 == 0)
	{
		philo_think(philo);
		accurate_sleep(philo->data->time_to_eat / 2);
	}
	while (read_bool(&philo->data->start_lock, &philo->data->dinner_start)
		&& philo->full == false)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*one_routine(t_philo *philo)
{
	mutex_handler(&philo->right_fork->fork, LOCK);
	philo_print(philo, FORK);
	mutex_handler(&philo->right_fork->fork, UNLOCK);
	while (read_bool(&philo->data->start_lock, &philo->data->dinner_start))
		usleep(100);
	return (NULL);
}
