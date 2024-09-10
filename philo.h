/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:14:49 by mgering           #+#    #+#             */
/*   Updated: 2024/09/10 14:38:55 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>	//INT_MAX
# include <stdbool.h>	//fot bool type
# include <string.h>	//memset
# include <stdio.h>		//printf
# include <stdlib.h>	//maloc, free
# include <unistd.h>	//write, usleep
# include <sys/time.h>	//gettimeofday
# include <errno.h>		//err return values for pthread
# include <pthread.h>	/* pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
*/
# define RED "\033[31m"	//Define ANSI escape sequences for colors and styles
# define GR "\033[32m"
# define YEL "\033[33m"
# define BL "\033[34m"
# define RST "\033[0m"

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			meal_time;
	bool			can_eat;
	bool			full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	philo_lock;
	pthread_mutex_t	bool_lock;
}	t_philo;

typedef struct s_data
{
	int				num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_of_meals;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	start_lock;
	bool			dinner_start;
}	t_data;

typedef enum e_operation
{
	CREATE,
	JOIN,
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}	t_operation;

typedef enum e_print
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_print;

//--------------philo.c---------------------
int		main(int argc, char **argv);
void	*start_dinner(t_data *data);
int		wait_all_philos(t_philo *philo);

//--------------philo_routine.c-------------
void	*philo_routine(void *arg);
void	*one_routine(t_philo *philo);

//--------------philo_check.c---------------
void	*check_philos_full(void *arg);
void	*check_philos_alive(void *arg);
void	stop_dinner(t_data *data, int *i);

//--------------time_utils.c----------------
void	accurate_sleep(long msec);
long	current_time_ms(void);

//--------------check.c---------------------
int		input_check(char **argv);
long	ft_atol(const char *str);
void	*ft_calloc(size_t nitems, size_t size);

//--------------init.c----------------------
int		input_data(char **argv, t_data *data);
int		alloc_data(t_data *data);
void	*init_philo(t_data *data, int *i);

//--------------thread_utils.c--------------
int		error_msg(int ret, const char *err_msg);
int		mutex_handler(pthread_mutex_t *mutex, t_operation operation);
int		thread_handler(t_philo *philp, t_operation operation);

//--------------message.c-------------------
int		philo_print(t_philo *philo, t_print msg);

//--------------philo_state.c---------------
void	*philo_eat(t_philo *philo);
int		assign_forks(t_philo *philo, t_fork **first, t_fork **second);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_died(t_philo *philo);

//--------------mtx_utils.c------------------
bool	read_bool(pthread_mutex_t *mtx, bool *dst);
void	write_bool(pthread_mutex_t *mtx, bool *dst, bool src);
long	read_time(pthread_mutex_t *mtx, long *dst);
void	write_long(pthread_mutex_t *mtx, long *dst, long src);

//--------------free_resources.c-------------
void	free_data(t_data *data);

#endif