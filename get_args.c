/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parmando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:34:12 by parmando          #+#    #+#             */
/*   Updated: 2024/11/22 04:34:16 by parmando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
		pthread_create(&table->philos[i].thread, NULL,
			actions, (void *)&table->philos[i]);
	controller(table->philos);
	i = -1;
	while (++i < table->num_philos)
		pthread_join(table->philos[i].thread, NULL);
	i = -1;
	while (++i < table->num_philos)
		pthread_mutex_destroy(&table->forks[i].fork);
}

static void	init_values(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = get_time();
	while (++i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].id = i;
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].table = table;
		table->philos[i].last_meal_time = table->start_time;
	}
	i = -1;
	while (++i < table->num_philos)
	{
		table->philos[i].f_fork = &table->forks[i];
		table->philos[i].s_fork = &table->forks[(i + 1) % table->num_philos];
	}
}

void	get_args(t_table *table, char **argv)
{
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->meals_required = -1;
	if (argv[5])
		table->meals_required = ft_atoi(argv[5]);
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philos);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->num_philos);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->eaten, NULL);
	pthread_mutex_init(&table->end_check, NULL);
	table->end = false;
	init_values(table);
	init_philos(table);
}
