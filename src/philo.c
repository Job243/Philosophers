/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:29:58 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/30 19:29:46 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*init_table(t_table *table, int ac, char **av)
{
	if (ac == 6)
		table->total_meals = ft_atol(av[5]);
	else
		table->total_meals = -1;
	table->all_alive = 1;
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->philo = malloc(sizeof(t_philosopher) * table->philo_nbr);
	pthread_mutex_init(&table->all_alive_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	if (!table->philo)
	{
		free(table->philo);
		free(table);
		return (NULL);
	}
	return (table);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!valid_arg(ac, av))
		return (1);
	memset(&table, 0, sizeof(t_table));
	init_table(&table, ac, av);
	start_simulation(&table);
	while (1)
	{
		if (!check_philos(&table))
			break ;
	}
	join_threads(&table);
	clean_up(&table);
	return (0);
}

/*
	1 300 200 200 ne sarrete pas

*/
