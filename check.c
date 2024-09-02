/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:50:07 by mgering           #+#    #+#             */
/*   Updated: 2024/09/02 17:12:44 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_check(char **argv)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (argv[++i])
	{
		result = ft_atol(argv[i]);
		if (result <= 0)
		{
			write(2, "no valid num or 0\n", 19);
			return (-1);
		}
		else if (result > INT_MAX)
		{
			write(2, "bigger INT_MAX\n", 16);
			return (-1);
		}
		else if ((i == 2 || i == 3 || i == 4) && result < 60)
		{
			write(2, "timestamp < 60\n", 16);
			return (-1);
		}
	}
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	result = result * sign;
	return (result);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*memory_ptr;
	size_t	i;

	i = 0;
	memory_ptr = malloc(nitems * size);
	if (!memory_ptr)
		return (NULL);
	while (i < (nitems * size))
	{
		*((unsigned char *)memory_ptr + i) = '\0';
		i++;
	}
	return (memory_ptr);
}
