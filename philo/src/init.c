/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:31:05 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/12 16:11:58 by jmafueni         ###   ########.fr       */
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

void	init_philosophers(t_table *table)
{
	int		i;
	long	z;

	i = 0;
	z = get_time();
	while (i < table->philo_nbr)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal = z;
		if (i + 1 != table->philo_nbr)
			table->philo[i].right_fork = &table->philo[i + 1].left_fork;
		else
			table->philo[i].right_fork = &table->philo[0].left_fork;
		pthread_mutex_init(&table->philo[i].left_fork, NULL);
		pthread_mutex_init(&table->philo[i].meal_mutex, NULL);
		pthread_mutex_init(&table->philo[i].meal_time, NULL);
		pthread_mutex_init(&table->philo[i].ph_mutex, NULL);
		table->philo[i].table = table;
		i++;
	}
	table->start_time = z;
}

void	created_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philo[i].thread, NULL, philosopher_routine,
			&table->philo[i]);
		i++;
	}
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			printf("Failed to join thread number %d\n", i);
		i++;
	}
}

void	start_simulation(t_table *table)
{
	init_philosophers(table);
	created_threads(table);
}
