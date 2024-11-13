/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:53:15 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/13 21:11:06 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_alive(t_philosopher *philo)
{
	int	alive_status;

	pthread_mutex_lock(&philo->table->all_alive_mutex);
	alive_status = philo->table->all_alive;
	pthread_mutex_unlock(&philo->table->all_alive_mutex);
	return (alive_status);
}

int	check_n_handle_death(t_philosopher *philo)
{
	long	current_time;
	long	last_meal;

	pthread_mutex_lock(&philo->meal_time);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_time);
	current_time = get_time();
	if (current_time - last_meal > philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf(RED"%ld %d died\n"RST,
			current_time - philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_lock(&philo->table->all_alive_mutex);
		philo->table->all_alive = 0;
		pthread_mutex_unlock(&philo->table->all_alive_mutex);
		return (1);
	}
	return (0);
}

int	check_total_meals(t_philosopher *philo)
{
	int	i;
	int	full;

	if (philo->table->total_meals < 0)
		return (0);
	i = 0;
	full = 1;
	while (i < philo->table->philo_nbr)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (philo[i].meals_eaten < philo->table->total_meals)
			full = 0;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	return (full);
}

int	check_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (check_total_meals(table->philo))
			return (0);
		if (check_n_handle_death(&table->philo[i]))
			return (0);
		i++;
	}
	return (1);
}
