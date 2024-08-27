/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:31:53 by mgering           #+#    #+#             */
/*   Updated: 2024/08/27 14:54:44 by mgering          ###   ########.fr       */
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
			if (-1 == init_data(argv, &data))
			{
				printf("Data initialize failed");
				return (-1);
			}
			start_dinner(&data);
		}
		//cleanup need to do
	}
	else
		printf("wrong Number of Parameters");
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->dinner_start)
		usleep(10);
	if (philo->data->num_of_philos == 1)
		;//routine for one philo
	else if ((philo->id + 1) % 2 == 0)
	{
		philo_think(philo);
		philo->philo_time += accurate_sleep(philo->data->time_to_eat / 2);
	}
	while (philo->data->dinner_start == true
		&& philo->is_dead == false && philo->data->num_of_philos > 1)
	{
		if (philo->full || philo->is_dead)
			break ;
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
	if (1 == data->num_of_philos)
		return (NULL);//extra fucntion for one philo need to do
	while (++i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].meal_time = 0;
		data->philos[i].philo_time = 0;
		data->philos[i].is_dead = false;
		data->philos[i].full = false;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->num_of_philos];
		data->philos[i].data = data;
		if (0 != thread_handler(&data->philos[i], CREATE))
			break ;
	}
	data->dinner_start = true;
	data->dinner_time_start = current_time_us();
	while (++j < i)
		thread_handler(&data->philos[j], JOIN);
	return (NULL);
}



/* void	*test_func(void *add);
pthread_mutex_t	mutex;

int main()
{
	pthread_t	test;
	pthread_t	test2;

	long	value1;
	value1 = 0;

 	pthread_mutex_init(&mutex, NULL);
    pthread_create(&test, NULL, test_func, (void*) &value1);
	pthread_create(&test2, NULL, test_func, (void*)&value1);

	pthread_join(test, NULL);
	pthread_join(test2, NULL);

	pthread_create(&test, NULL, test_func, (void*) &value1);
	pthread_create(&test2, NULL, test_func, (void*)&value1);

	pthread_join(test, NULL);
	pthread_join(test2, NULL);
	pthread_mutex_destroy(&mutex);

    return 0;
}

void	*test_func(void *add)
{


	pthread_mutex_lock(&mutex);
	long	*add_num = (long *)(add);
	long	i = 0;

	while (i <= 1000000000)
	{
		i++;
		(*add_num)++;
	}
	printf("Add: %ld\n", *add_num);
	pthread_mutex_unlock(&mutex);
	return (NULL);
} */
