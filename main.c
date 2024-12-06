/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parmando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:42:50 by parmando          #+#    #+#             */
/*   Updated: 2024/10/14 11:59:19 by parmando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verify(char **argv)
{
	int	i;
	int	t;

	t = 0;
	while (argv[++t])
	{
		i = -1;
		if (ft_atoi(argv[t]) <= 0 || ft_atoi(argv[t]) > 2147483647)
			return (0);
		while (argv[t][++i] != '\0')
		{
			if (argv[t][i] == '+' && i == 0)
				i++;
			if (!ft_isdigit(argv[t][i]))
				return (0);
		}
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if ((argc != 5 && argc != 6) || verify(argv) != 1)
		return (0);
	get_args(&table, argv);
	pthread_mutex_destroy(&table.print);
	pthread_mutex_destroy(&table.eaten);
	pthread_mutex_destroy(&table.end_check);
	free(table.forks);
	free(table.philos);
	return (0);
}
