/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:24:50 by mgering           #+#    #+#             */
/*   Updated: 2024/09/12 17:53:24 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_eat(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	first_fork = NULL;
	second_fork = NULL;
	if (0 > assign_forks(philo, &first_fork, &second_fork))
		return (NULL);
	if (!read_bool(&philo->data->start_lock, &philo->data->dinner_start))
		return (NULL);
	mutex_handler(&first_fork->fork, LOCK);
	philo_print(philo, FORK);
	mutex_handler(&second_fork->fork, LOCK);
	philo_print(philo, FORK);
	philo_print(philo, EAT);
	write_long(&philo->philo_lock, &philo->meal_time, current_time_ms());
	accurate_sleep(philo->data->time_to_eat);
	mutex_handler(&first_fork->fork, UNLOCK);
	mutex_handler(&second_fork->fork, UNLOCK);
	write_bool(&philo->bool_lock, &philo->can_eat, false);
	philo->meals_eaten++;
	if (philo->data->num_of_meals == philo->meals_eaten)
		write_bool(&philo->bool_lock, &philo->full, true);
	return (NULL);
}

int	assign_forks(t_philo *philo, t_fork **first, t_fork **second)
{
	while (!read_bool(&philo->bool_lock, &philo->can_eat))
	{
		if (!read_bool(&philo->data->start_lock, &philo->data->dinner_start))
			return (-1);
		usleep(100);
	}
	if (philo->id != philo->data->num_of_philos)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	philo_print(philo, SLEEP);
	accurate_sleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	philo_print(philo, THINK);
}
