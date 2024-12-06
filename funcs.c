/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parmando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:42:50 by parmando          #+#    #+#             */
/*   Updated: 2024/10/14 11:59:19 by parmando         ###   ########.fr       */
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

bool	check_end(t_table *table)
{
	bool	status;

	pthread_mutex_lock(&table->end_check);
	status = table->end;
	pthread_mutex_unlock(&table->end_check);
	return (status);
}

void	put_state(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	if (check_end(philo->table) == false)
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
