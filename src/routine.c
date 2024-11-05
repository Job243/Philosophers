/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:13:36 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/01 19:13:55 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void	eat(t_philosopher *philo)
// {
// 	take_forks(philo);
// 	pthread_mutex_lock(&philo->meal_mutex);
// 	print_action(philo, Y"is eating "RST);
// 	philo->last_meal = get_time();
// 	usleep(philo->table->time_to_eat * 1000);
// 	philo->meals_eaten++;
// 	pthread_mutex_unlock(&philo->meal_mutex);
// 	release_forks(philo);
// }

// void	think_n_sleep(t_philosopher *philo)
// {
// 	if (!is_alive(philo) && (philo->meals_eaten >= philo->table->total_meals
// 			|| philo->table->total_meals != -1))
// 		return ;
// 	print_action(philo, B"is sleeping"RST);
// 	usleep(philo->table->time_to_sleep * 1000);
// 	// pthread_mutex_lock(&philo->table->all_alive_mutex);
// 	// if (!philo->table->all_alive)
// 	// {
// 	// 	pthread_mutex_unlock(&philo->table->all_alive_mutex);
// 	// 	pthread_exit(NULL);
// 	// }
// 	// pthread_mutex_unlock(&philo->table->all_alive_mutex);
// 	if (!is_alive(philo) && (philo->meals_eaten >= philo->table->total_meals
// 			|| philo->table->total_meals != -1))
// 		return ;
// 	print_action(philo, BLUE"is thinking"RST);
// 	usleep(200);
// }

// void	take_forks(t_philosopher *philo)
// {

// 	if (philo->id % 2 != 0)
// 	{
// 		pthread_mutex_lock(philo->right_fork);
// 		print_action(philo, M"has taken the right fork"RST);
// 		pthread_mutex_lock(philo->left_fork);
// 		print_action(philo, C"has taken the left fork"RST);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		print_action(philo, C"has taken the left fork"RST);
// 		pthread_mutex_lock(philo->right_fork);
// 		print_action(philo, M"has taken the right fork"RST);
// 	}
// }

// void	release_forks(t_philosopher *philo)
// {
// 	pthread_mutex_unlock(philo->right_fork);
// 	pthread_mutex_unlock(philo->left_fork);
// }

int	eat(t_philosopher *philo)
{
	if (philo->id % 2 != 0)
	{
		if (!take_forks_odd(philo))
			return (0);
	}
	else
		take_forks_even(philo);
	pthread_mutex_lock(&philo->meal_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time);
	if (!is_alive(philo))
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_action(philo, Y "is eating" RST);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (1);
}

int	sleep_philo(t_philosopher *philo)
{
	if (is_alive(philo) == 0)
		return (0);
	print_action(philo, B "is sleeping" RST);
	usleep(philo->table->time_to_sleep * 1000);
	return (1);
}

int	think(t_philosopher *philo)
{
	(void)philo;
	if (is_alive(philo) == 0)
		return (0);
	print_action(philo, BLUE "is thinking" RST);
	while (get_time() - philo->last_meal < philo->table->time_to_die - 50)
		usleep(10);
	return (1);
}

void	one_philo_handler(t_table *table)
{
	usleep(table->time_to_die);
	// print_action(table->philo, "has died");
}

int	take_forks_odd(t_philosopher *philo)
{
	if (!is_alive(philo))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	if (philo->table->philo_nbr == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		one_philo_handler(philo->table);
		return (0);
	}
	if (is_alive(philo) != 0)
		print_action(philo, M "right fork has taken a fork" RST);
	else
		return (0);
	pthread_mutex_lock(&philo->left_fork);
	if (is_alive(philo) != 0)
		print_action(philo, C "left fork has taken a fork" RST);
	else
		return (0);
	return (1);
}
