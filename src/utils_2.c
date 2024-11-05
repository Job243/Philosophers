/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:53:15 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/01 20:06:02 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	take_forks_even(t_philosopher *philo)
{
	if (!is_alive(philo))
		return (0);
	pthread_mutex_lock(&philo->left_fork);
	if (!is_alive(philo))
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (0);
	}
	if (is_alive(philo) != 0)
		print_action(philo, M "has taken a fork" RST);
	pthread_mutex_lock(philo->right_fork);
	if (!is_alive(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	if (is_alive(philo) != 0)
		print_action(philo, C "has taken a fork" RST);
	return (1);
}

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
	long 	current_time;
	long 	last_meal;

	pthread_mutex_lock(&philo->meal_time);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_time);
	pthread_mutex_lock(&philo->meal_mutex);
	// printf("CHECKKKK DE PHILO %d\n", philo->id);
	current_time = get_time();
	if (current_time - last_meal > philo->table->time_to_die)
	{
		// printf("%lld\n", current_time - philo->last_meal);
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_lock(&philo->table->all_alive_mutex);
		philo->table->all_alive = 0;
		pthread_mutex_unlock(&philo->table->all_alive_mutex);
		usleep(100);
		print_action(philo, RED " died" RST);

		// printf("%d\n", philo->table->time_to_die);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
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
	// if (table->philo_nbr == 1)
	// {
	// 	one_philo_handler(table);
	// 	break ;
	// }

	// 	pthread_mutex;_lock(&table->all_alive_mutex);
	// 	if (!table->all_alive)
	// 	{
	// 		pthread_mutex_unlock(&table->all_alive_mutex);
	// 		break ;
	// 	}
	// 	pthread_mutex_unlock(&table->all_alive_mutex);
	// 	i = 0;
	// }
	return (1);
}

void	clean_up(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->philo[i].meal_mutex);
		pthread_mutex_destroy(&table->philo[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&table->all_alive_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->philo);
}
