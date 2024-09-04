/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:31:53 by mgering           #+#    #+#             */
/*   Updated: 2024/09/04 14:28:52 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void check_leaks(void)
// {
//     system("leaks philo");
// }
// 		atexit(check_leaks);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (-1 == input_check(argv))
		{
			printf("Example: ./philo 5 500 200 200 5\n");
			return (-1);
		}
		else
		{
			if (-1 == input_data(argv, &data))
			{
				printf("Data initialize failed\n");
				return (-1);
			}
			start_dinner(&data);
		}
		free_data(&data);
	}
	else
		printf("wrong Number of Parameters\n");
	return (0);
}

void	*start_dinner(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (0 == data->num_of_meals)
		return (NULL);
	init_philo(data, &i);
	write_bool(&data->start_lock, &data->dinner_start, true);
	check_philos(data);
	while (++j < i)
		thread_handler(&data->philos[j], JOIN);
	return (NULL);
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
