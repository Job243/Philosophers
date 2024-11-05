/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:31:05 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/01 19:21:53 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_philosophers(t_table *table)
{
	int	i;
	long z = get_time();
	i = 0;
	while (i < table->philo_nbr)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal = z;
		table->philo[i].right_fork = &table->philo[(i + 1) % table->philo_nbr].left_fork;
		pthread_mutex_init(&table->philo[i].left_fork, NULL);
		pthread_mutex_init(&table->philo[i].meal_mutex, NULL);
		pthread_mutex_init(&table->philo[i].meal_time, NULL);
		pthread_mutex_init(&table->philo[i].ph_mutex, NULL);
		table->philo[i].table = table;
		i++;
	}
	table->start_time = z;

}

// void	*philosopher_routine(void *arg)
// {
// 	t_philosopher	*philo;

// 	philo = (t_philosopher *)arg;
// 	while (is_alive(philo) && (philo->table->total_meals == -1
// 			|| philo->meals_eaten < philo->table->total_meals))
// 	{
// 		eat(philo);
// 		think_n_sleep(philo);
// 	}
// 	return (NULL);
//  is_alive(philo) && (philo->table->total_meals == -1
			// || philo->meals_eaten < philo->table->total_meals)}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (is_alive(philo) == 0)
			break ;
		if (!eat(philo))
			break ;
		if (is_alive(philo) == 0)
			return (0);
		if (sleep_philo(philo) == 0)
			break ;
		if (think(philo) == 0)
			break ;
	}
	return (0);
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
