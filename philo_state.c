/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:24:50 by mgering           #+#    #+#             */
/*   Updated: 2024/08/30 13:13:54 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	mutex_handler(&philo->left_fork->fork, LOCK);
	philo_print(philo, L_FORK);
	mutex_handler(&philo->right_fork->fork, LOCK);
	philo_print(philo, R_FORK);
	philo_print(philo, EAT);
	write_long(&philo->philo_lock, &philo->meal_time, current_time_ms());
	accurate_sleep(philo->data->time_to_eat);
	write_long(&philo->philo_lock, &philo->meal_time, current_time_ms());
	mutex_handler(&philo->left_fork->fork, UNLOCK);
	mutex_handler(&philo->right_fork->fork, UNLOCK);
	philo->meals_eaten++;
	if (philo->data->num_of_meals == philo->meals_eaten)
		write_bool(&philo->philo_lock, &philo->full, true);
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

void	philo_died(t_philo *philo)
{
	philo->is_dead = true;
	philo_print(philo, DEAD);
}
