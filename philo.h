/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:01:23 by parmando          #+#    #+#             */
/*   Updated: 2025/02/13 12:59:48 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct timeval	t_time;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	bool				end;
	long			last_meal_time;
	long			meals_eaten;
	t_fork			*f_fork;
	t_fork			*s_fork;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long				num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_required;
	long				start_time;
	t_fork				*forks;
	t_philo				*philos;
	pthread_t			controller;
	pthread_mutex_t		print;
	pthread_mutex_t		eaten;
	pthread_mutex_t		end_check;
	pthread_mutex_t		nmb_meals;
}	t_table;

int						ft_atoi(const char *nptr);
int						ft_isdigit(int c);
long long				get_time(void);
void	*controller(void *args);
void					get_args(t_table *table, char **argv);
void					*actions(void *arg);
void					put_state(char *msg, t_philo *philo);
bool get_state(t_philo *philo);
long get_last_meal_time(t_philo *philo);

#endif
