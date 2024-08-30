/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:31:53 by mgering           #+#    #+#             */
/*   Updated: 2024/08/30 13:56:44 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (-1 == input_check(argv))
			printf("Example: ./philo 800 200 200 200 5\n");
		else
		{
			if (-1 == input_data(argv, &data))
			{
				printf("Data initialize failed");
				return (-1);
			}
			start_dinner(&data);
		}
		free_data(&data);
	}
	else
		printf("wrong Number of Parameters");
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (wait_all_philos(philo))
		;
	write_long(&philo->philo_lock, &philo->start_time, current_time_ms());
	write_long(&philo->philo_lock, &philo->meal_time, current_time_ms());
	if (philo->data->num_of_philos == 1)
		;//routine for one philo
	else if ((philo->id + 1) % 2 == 0)
	{
		philo_think(philo);
		accurate_sleep(philo->data->time_to_eat / 2);
	}
	while (read_bool(&philo->data->start_lock, &philo->data->dinner_start)
		&& !read_bool(&philo->philo_lock, &philo->is_dead) //try without
		&& philo->full == false)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*start_dinner(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (0 == data->num_of_meals)
		return (NULL);
/* 	if (1 == data->num_of_philos)
		return (NULL);//extra fucntion for one philo need to do */
	while (++i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].meal_time = current_time_ms();
		data->philos[i].is_dead = false;
		data->philos[i].full = false;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->num_of_philos];
		data->philos[i].data = data;
		mutex_handler(&data->philos[i].philo_lock, INIT);
		if (0 != thread_handler(&data->philos[i], CREATE))
			break ;
	}
	write_bool(&data->start_lock, &data->dinner_start, true);
	check_philos(data);
	while (++j < i)
		thread_handler(&data->philos[j], JOIN);
	return (NULL);
}

void	check_philos(t_data *data)
{
	int	i;

	while (read_bool(&data->start_lock, &data->dinner_start))
	{
		i = -1;
		while (++i < data->num_of_philos)
			check_alive(&data->philos[i]);
		if (check_philos_full(data))
			write_bool(&data->start_lock, &data->dinner_start, false);
	}
}

bool	check_philos_full(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		if (!read_bool(&data->philos[i].philo_lock, &data->philos[i].full))
			return (false);
	}
	return (true);
}

void	check_alive(t_philo *philo)
{
	long	time;

	mutex_handler(&philo->philo_lock, LOCK);
	time = current_time_ms() - philo->meal_time;
	if (time >= philo->data->time_to_die)
	{
		philo_print(philo, DEAD);
		write_bool(&philo->data->start_lock, &philo->data->dinner_start, false);
		philo->is_dead = true;
	}
	mutex_handler(&philo->philo_lock, UNLOCK);
}

int	wait_all_philos(t_philo *philo)
{
	mutex_handler(&philo->data->start_lock, LOCK);
	if (philo->data->dinner_start)
	{
		mutex_handler(&philo->data->start_lock, UNLOCK);
		return (0);
	}
	mutex_handler(&philo->data->start_lock, UNLOCK);
	return (1);
}
