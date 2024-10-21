/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:29:58 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/21 17:01:46 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*init_table(int philo_nbr)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_nbr = philo_nbr;
	table->philo = malloc(sizeof(t_philosopher) * philo_nbr);
	table->forks = malloc(sizeof(pthread_mutex_t) * philo_nbr);
	table->all_alive = 1;
	pthread_mutex_init(&table->all_alive_mutex, NULL);
	if (!table->philo || !table->forks)
	{
		free(table->philo);
		free(table->forks);
		free(table);
		return (NULL);
	}
	return (table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac < 5 || ac > 6)
		ft_error(RED"Wrong input/n"RST G"Usage: <number_of_philosopher>"RST
			G"<time_to_die> <time_to_eat> <time_to_sleep>\n"RST);
	table = init_table(ft_atol(av[1]));
	if (!table)
		ft_error(RED"Failed to initialize  table."RST);
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		table->total_meals = ft_atol(av[5]);
	else
		table->total_meals = -1;
	start_simulation(table);
	return (0);
}

/*
	1. faire un cas special pour un seul:
		wait time to die puis le faire mourir

	2. ./philo 3 120 60 60
		infinite loop
	3. enlever release firks

	4.

*/
