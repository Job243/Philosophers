/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:13:36 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/21 00:03:15 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	eat(t_philosopher *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	print_action(philo, Y"is eating "RST);
	philo->last_meal = get_time();
	usleep(philo->table->time_to_eat * 1000);
	philo->meals_eaten++;
	printf("Philosopher %d has eaten %d meals.\n", philo->id, philo->meals_eaten);
	pthread_mutex_unlock(&philo->meal_mutex);
	release_forks(philo);
}

void	sleep_philo(t_philosopher *philo)
{
	if (!is_alive(philo))
		return ;
	print_action(philo, B"is sleeping"RST);
	usleep(philo->table->time_to_sleep * 1000);
}

void	think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->all_alive_mutex);
	if (!philo->table->all_alive)
	{
		pthread_mutex_unlock(&philo->table->all_alive_mutex);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philo->table->all_alive_mutex);
	print_action(philo, BLUE"is thinking"RST);
	usleep(200);
}


void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, M"has taken the right fork"RST);

		pthread_mutex_lock(philo->left_fork);
		print_action(philo, C"has taken the left fork"RST);
	}
	else
	{
		// usleep(100);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, C"has taken the left fork"RST);

		pthread_mutex_lock(philo->right_fork);
		print_action(philo, M"has taken the right fork"RST);
	}
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

