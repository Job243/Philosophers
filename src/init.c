/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:31:05 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/09 22:12:58 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void	init_philosopers(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	table->philo = malloc(sizeof(t_philosopher) * table->philo_nbr);
// 	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
// 	while (i < table->philo_nbr)
// 	{
// 		table->philo[i].id = i + 1;
// 		table->philo[i].meals_eaten = 0;
// 		table->philo[i].left_fork = &table->forks[i];
// 		table->philo[i].right_fork = &table->forks[(i + 1) % table->philo_nbr];
// 		pthread_mutex_init(&table->forks[i], NULL);
// 		i++;
// 	}
// }

// void	create_thread(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	while (i < table->philo_nbr)
// 	{
// 		pthread_create(&table->philo[i].thread, NULL,
			// philosopher_routine, &table->philo[i]);
// 		i++;
// 	}
// 	while (i < table->philo_nbr)
// 	{
// 		pthread_join(&table->philo[i].thread, NULL);
// 		i++;
// 	}
// }

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

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo->table->all_alive && (philo->table->total_meals == -1
		|| philo->meals_eaten < philo->table->total_meals))
	{
		print_action(philo->id, "is thinking");
		usleep(100);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			print_action(philo->id, "has taken the right fork");
			pthread_mutex_lock(philo->left_fork);
			print_action(philo->id, "has taken the left fork");
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			print_action(philo->id, "has taken the left fork");
			pthread_mutex_lock(philo->right_fork);
			print_action(philo->id, "has taken the right fork");
		}
		pthread_mutex_lock(&philo->meal_mutex);
		print_action(philo->id, "is eating ");
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->meal_mutex);
		usleep(philo->table->time_to_eat * 1000);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action(philo->id, "is sleeping");
		usleep(philo->table->time_to_sleep * 1000);
	}
	return (NULL);
}

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
	check_philos(table);
	join_threads(table);
	pthread_join(monitor_thread, NULL);
}
