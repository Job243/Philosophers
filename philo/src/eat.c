/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:07:57 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/13 21:14:10 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	take_forks_odd(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (print_action(philo, C"has taken a fork"RST) == true)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->left_fork);
	if (print_action(philo, M"has taken a fork"RST) == true)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		return (0);
	}
	return (1);
}

int	take_forks_even(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	if (print_action(philo, M"has taken a fork"RST) == true)
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	if (print_action(philo, C"has taken a fork"RST) == true)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (1);
}

int	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 != 0)
	{
		if (!take_forks_odd(philo))
			return (0);
	}
	else
	{
		if (take_forks_even(philo) == 0)
			return (0);
	}
	return (1);
}

int	meals_eaten(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table->total_meals)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (1);
}

int	eat(t_philosopher *philo)
{
	if (!take_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->meal_time);
	if (print_action(philo, Y"is eating"RST) == true)
		return (pthread_mutex_unlock(&philo->meal_time), 0);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time);
	if (ft_usleep(philo->table->time_to_eat, philo) == 0)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!meals_eaten(philo))
		return (0);
	return (1);
}
