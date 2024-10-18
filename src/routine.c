/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:13:36 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/18 20:00:07 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	eat(t_philosopher *philo)
{
	if (!is_alive(philo))
		return ;
	pthread_mutex_lock(&philo->meal_mutex);
	print_action(philo->id, Y"is eating "RST);
	philo->last_meal = get_time();
	usleep(philo->table->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	sleep_philo(t_philosopher *philo)
{
	if (!is_alive(philo))
		return ;
	print_action(philo->id, B"is sleeping"RST);
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
	print_action(philo->id, BLUE"is thinking"RST);
	usleep(200);
}

void	take_forks(t_philosopher *philo)
{
	if (!is_alive(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		if (!is_alive(philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		print_action(philo->id, M"has taken the right fork"RST);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo->id, C"has taken the left fork"RST);
	}
	else
	{
		usleep(200);
		if (!is_alive(philo))
			return ;
		pthread_mutex_lock(philo->left_fork);
		print_action(philo->id, C"has taken the left fork"RST);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo->id, M"has taken the right fork"RST);
	}
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->all_alive_mutex);
	if (philo->table->all_alive)
	{
		print_action(philo->id, "is releasing the forks");
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	pthread_mutex_unlock(&philo->table->all_alive_mutex);
}
