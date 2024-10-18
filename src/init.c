/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:31:05 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/15 23:04:17 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal = get_time();
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->philo_nbr];
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&table->philo[i].meal_mutex, NULL);
		table->philo[i].table = table;
		i++;
	}
	assign_philo_number(table);
}

// void	*philosopher_routine(void *arg)
// {
// 	t_philosopher	*philo;

// 	philo = (t_philosopher *)arg;
// 	while (philo->table->all_alive && (philo->table->total_meals == -1
// 			|| philo->meals_eaten < philo->table->total_meals))
// 	{
// 		take_forks(philo);
// 		eat(philo);
// 		release_forks(philo);
// 		sleep_philo(philo);
// 		think(philo);
// 	}
// 	return (NULL);
// }

void	*philosopher_routine(void *arg)
{
	t_philosopher *philo = (t_philosopher *)arg;

	while (1)
	{
		if (!is_alive(philo))
			pthread_exit(NULL);
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_philo(philo);
		think(philo);
		if (!is_alive(philo))
			pthread_exit(NULL);
	}
	return (NULL);
}


// void	*philosopher_routine(void *arg)
// {
// 	t_philosopher	*philo;

// 	philo = (t_philosopher *)arg;
// 	while (1)
// 	{
// 		if (!is_alive(philo))
// 			pthread_exit(NULL);
// 		pthread_mutex_unlock(&philo->table->all_alive_mutex);
// 		take_forks(philo);
// 		eat(philo);
// 		pthread_mutex_lock(&philo->meal_mutex);
// 		philo->meals_eaten++; // Protected access to meals_eaten
// 		pthread_mutex_unlock(&philo->meal_mutex);
// 		release_forks(philo);
// 		sleep_philo(philo);
// 		think(philo);
// 	}
// 	pthread_exit(NULL);
// }


void	created_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philo[i].thread, NULL,
			philosopher_routine, &table->philo[i]);
		i++;
	}
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
}

void	start_simulation(t_table *table)
{
	pthread_t	monitor_thread;

	init_philosophers(table);
	created_threads(table);
	pthread_create(&monitor_thread, NULL, (void *)check_philos, table);
	join_threads(table);
	pthread_join(monitor_thread, NULL);
}
