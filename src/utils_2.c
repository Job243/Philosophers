/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:53:15 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/21 00:11:19 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_alive(t_philosopher *philo)
{
	long long	time_since_last_meal;

	pthread_mutex_lock(&philo->table->all_alive_mutex);
	if (!philo->table->all_alive)
	{
		pthread_mutex_unlock(&philo->table->all_alive_mutex);
		return (0); // Le philosophe n'est pas vivant
	}
	pthread_mutex_unlock(&philo->table->all_alive_mutex);

	time_since_last_meal = get_time() - philo->last_meal;
	if (time_since_last_meal < philo->table->time_to_die)
		return (1); // Le philosophe est vivant
	else
	return (0); // Le philosophe est mort
}


int	philosopher_died(t_philosopher *philo)
{
	int			died;
	long long	current_time;

	pthread_mutex_lock(&philo->meal_mutex);
	current_time = get_time();
	died = (current_time - philo->last_meal > philo->table->time_to_die);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (died);
}

void	handle_philosopher_death(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->all_alive_mutex);
	philo->table->all_alive = 0;
	pthread_mutex_unlock(&philo->table->all_alive_mutex);
	print_action(philo, RED" died"RST);
	usleep(10);
}

void	check_philos(t_table *table)
{
	int	i;

	while (1)
	{
		// if (check_total_meals(table->philo))
		// 	break ;
		pthread_mutex_lock(&table->all_alive_mutex);
		if (!table->all_alive)
		{
			pthread_mutex_unlock(&table->all_alive_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->all_alive_mutex);
		i = 0;
		while (i < table->philo_nbr)
		{
			if (philosopher_died(&table->philo[i]))
			{
				handle_philosopher_death(&table->philo[i]);
				return ;
			}
			i++;
		}
		usleep(100);
	}
}

void	clean_up(t_table *table)
{
	int	i;

	i = 0;
	// while (i < table->philo_nbr)
	// {
	// 	if (pthread_join(table->philo[i].thread, NULL) != 0)
	// 		printf(RED"Error : Failed to join thread %d\n"RST, i);
	// 	i++;
	// }
	// i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->philo[i].meal_mutex);
		pthread_mutex_destroy(table->philo[i].left_fork);
		pthread_mutex_destroy(table->philo[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(&table->all_alive_mutex);
	free(table->philo);
	free(table);
}
