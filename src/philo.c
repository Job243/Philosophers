/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:29:58 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/10 23:23:56 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*init_table(int	philo_nbr)
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
	int		philo_nbr;
	int		total_meals;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	t_table	*table;

	total_meals = -1;
	if (ac < 5 || ac > 6)
	{
		printf("Usage: <number_of_philosopher> <time_to_die> <time_to_eat> <time_to_sleep>\n");
		return (1);
	}
	philo_nbr = ft_atol(av[1]);
	time_to_die = ft_atol(av[2]);
	time_to_eat = ft_atol(av[3]);
	time_to_sleep = ft_atol(av[4]);

	if (ac == 6)
		total_meals = ft_atol(av[5]);
	table = init_table(philo_nbr);
	if (!table)
	{
		perror("Failed to initialize  table.");
		return (EXIT_FAILURE);
	}
	table->time_to_die = time_to_die;
	table->time_to_eat = time_to_eat;
	table->time_to_sleep = time_to_sleep;
	table->total_meals = total_meals;
	start_simulation(table);
	free(table->philo);
	free(table->forks);
	free(table);
	return (0);
}
