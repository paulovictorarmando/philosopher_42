/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:33:59 by parmando          #+#    #+#             */
/*   Updated: 2025/02/13 13:07:29 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_end_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->end_check);
		table->philos[i].end = true;
		pthread_mutex_unlock(&table->end_check);
	}
}


static bool	death_confirm(t_philo *philo)
{
	if (get_time() - get_last_meal_time(philo) >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->end_check);
		philo->end = true;
		printf("%lld %d %s\n", get_time() - philo->table->start_time,
			philo->id, "died");
		pthread_mutex_unlock(&philo->table->end_check);
		return (true);
	}
	return (false);
}

void	*controller(void *args)
{
	int		i;
	t_table *table;

	table = (t_table *)args;
	i = -1;
	while (++i < table->num_philos)
	{				
		if (death_confirm(&table->philos[i]) || get_state(&table->philos[i]))
		{
			set_end_all(table);
			break ;
		}
		if(i == table->num_philos - 1)
			i = -1;
	}
	return (NULL);
}
