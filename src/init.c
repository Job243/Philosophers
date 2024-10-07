/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:31:05 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/07 21:42:31 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_philosopers(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philosopher) * table->philo_nbr);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->philo_nbr];
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo->table->all_alive)
	{
		/*Pense*/
		print_action(philo->id, "is thinking");
		/*Prend un fork*/
		pthread_mutex_lock(philo->left_fork);
		print_action(philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo->id, "has taken a fork");
		/*Mange*/
		print_action(philo->id, "is eating ");
		philo->last_meal = get_time();
		usleep(philo->table->time_to_eat * 1000);
		philo->meals_eaten++;
		/*Repose les forks*/
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		/*Dodo*/
		print_action(philo->id, "is sleeping");
		usleep(philo->table->time_to_sleep * 1000);
	}
	return (NULL);
}

void	create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philo[i].thread, NULL, philosopher_routine, &table->philo[i]);
		i++;
	}
	while (i < table->philo_nbr)
	{
		pthread_join(&table->philo[i].thread, NULL);
		i++;
	}
}
/*void	init_philosophers_recursive(t_table *table, int i)
{
	if (i >= table->philo_nbr)
		return ;
	table->philo[i].id = i + 1;
	table->philo[i].meals_eaten = 0;
	table->philo[i].last_meal = 0;
	table->philo[i].left_fork = &table->forks[i];
	table->philo[i].right_fork = &table->forks[(i + 1) % table->philo_nbr];
	pthread_mutex_init(&table->forks[i], NULL);
	table->philo[i] = table;

	init_philosophers_recursive(table, i + 1);

}

void	created_threads_recursive(t_table *table, int i)
{
	if (i >= table->philo_nbr)
		return ;
	pthread_create(&table->philo[i].thread, NULL, philosopher_routine, &table->philo[i]);
	created_threads_recursive(table, i + 1);
}

void	join_threads_recursive(t_table *table, int i)
{
	if (i >= table->philo_nbr)
		return ;
	pthread_join(&table->philo[i].thread, NULL);
	join_threads_recursive(table, i + 1);
}

void	start_simulation(t_table *table)
{
	init_philosophers_recursive(table, 0);
	created_threads_recursive(table, 0);
	join_threads_recursive(table, 0);
}*/
