/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parmando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:34:30 by parmando          #+#    #+#             */
/*   Updated: 2024/11/22 04:34:34 by parmando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	one_philo(t_philo *philo)
{
	if (philo->table->num_philos == 1)
	{
		pthread_mutex_lock(&philo->f_fork->fork);
		put_state("has taken a fork", philo);
		usleep(philo->table->time_to_die);
		pthread_mutex_unlock(&philo->f_fork->fork);
		return (true);
	}
	return (false);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->f_fork->fork);
		put_state("has taken a fork", philo);
		pthread_mutex_lock(&philo->s_fork->fork);
		put_state("has taken a fork", philo);
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(&philo->s_fork->fork);
		put_state("has taken a fork", philo);
		pthread_mutex_lock(&philo->f_fork->fork);
		put_state("has taken a fork", philo);
	}
}

static void	routine(t_philo *philo)
{
	while (!check_end(philo->table))
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->table->eaten);
		put_state("is eating", philo);
		philo->last_meal_time = get_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->table->eaten);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->f_fork->fork);
		pthread_mutex_unlock(&philo->s_fork->fork);
		put_state("is sleeping", philo);
		usleep(philo->table->time_to_sleep * 1000);
		put_state("is thinking", philo);
	}
}

void	*actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (one_philo(philo))
		return (NULL);
	while (true)
	{
		if (check_end(philo->table))
			return (NULL);
		routine(philo);
	}
}
