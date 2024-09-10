/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:31:53 by mgering           #+#    #+#             */
/*   Updated: 2024/09/10 14:41:00 by mgering          ###   ########.fr       */
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
	pthread_t	philo_check_full;
	pthread_t	philo_check_dead;
	int			i;
	int			j;

	i = -1;
	j = -1;
	if (0 == data->num_of_meals)
		return (NULL);
	pthread_mutex_lock(&data->print_lock);
	init_philo(data, &i);
	write_long(&data->start_lock, &data->start_time, current_time_ms());
	pthread_mutex_unlock(&data->print_lock);
	if (0 != pthread_create(&philo_check_full, NULL, check_philos_full, data))
		return (NULL);
	if (0 != pthread_create(&philo_check_dead, NULL, check_philos_alive, data))
		return (NULL);
	while (++j < i)
		thread_handler(&data->philos[j], JOIN);
	pthread_join(philo_check_full, NULL);
	pthread_join(philo_check_dead, NULL);
	return (NULL);
}
