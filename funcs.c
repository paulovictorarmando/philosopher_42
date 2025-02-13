/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:42:50 by parmando          #+#    #+#             */
/*   Updated: 2025/02/13 13:07:14 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	index;
	int	number;

	index = 0;
	sign = 1;
	number = 0;
	while (nptr[index] == ' ' || nptr[index] == '\n' || nptr[index] == '\t'
		|| nptr[index] == '\v' || nptr[index] == '\f' || nptr[index] == '\r')
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			sign *= -1;
		index++;
	}
	while (nptr[index] >= 48 && nptr[index] <= 57)
	{
		number = number * 10 + (nptr[index] - 48);
		index++;
	}
	return (number * sign);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
void	put_state(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	if (!get_state(philo))
		printf("%lld %d %s\n", get_time() - philo->table->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&philo->table->print);
}

long long	get_time(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long get_last_meal_time(t_philo *philo)
{
	long	last_meal_time;
	pthread_mutex_lock(&philo->table->nmb_meals);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->nmb_meals);
	return (last_meal_time);
}
