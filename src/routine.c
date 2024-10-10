/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:13:36 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/10 22:37:45 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	print_action(philo->id, "is eating ");
	philo->last_meal = get_time();
	usleep(philo->table->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	sleep_philo(t_philosopher *philo)
{
	print_action(philo->id, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void	think(t_philosopher *philo)
{
	print_action(philo->id, "is thinking");
	usleep(200);
}

void	take_forks(t_philosopher *philo)
{
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
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
