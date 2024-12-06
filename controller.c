/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parmando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:33:59 by parmando          #+#    #+#             */
/*   Updated: 2024/11/22 04:34:04 by parmando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_end(t_table *table)
{
	pthread_mutex_lock(&table->end_check);
	table->end = true;
	pthread_mutex_unlock(&table->end_check);
}

static bool	full_eat(t_philo *philos)
{
	int	i;
	int	eaten;

	i = -1;
	eaten = 0;
	if (philos->table->meals_required == -1)
		return (false);
	while (++i < philos->table->num_philos)
	{
		pthread_mutex_lock(&philos->table->eaten);
		if (philos[i].meals_eaten >= philos->table->meals_required)
			eaten++;
		pthread_mutex_unlock(&philos->table->eaten);
	}
	return (eaten == philos->table->num_philos);
}

static bool	death_confirm(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eaten);
	if (get_time() - philo->last_meal_time >= philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->eaten);
		put_state("died", philo);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->eaten);
	return (false);
}

void	controller(t_philo *philos)
{
	int		i;

	while (true)
	{
		i = -1;
		while (++i < philos->table->num_philos)
		{
			if (death_confirm(&philos[i]))
			{
				set_end(philos->table);
				return ;
			}
		}
		if (full_eat(philos))
		{
			set_end(philos->table);
			return ;
		}
	}
}
