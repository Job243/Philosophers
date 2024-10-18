/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:53:15 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/19 01:14:38 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_alive(t_philosopher *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->table->all_alive_mutex);
	alive = philo->table->all_alive;
	pthread_mutex_unlock(&philo->table->all_alive_mutex);
	return (alive);
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
	clean_up(philo->table);
}

void	check_philos(t_table *table)
{
	int	i;

	while (1)
	{
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
		printf("routine\n");
			if (philosopher_died(&table->philo[i]))
			{
				handle_philosopher_death(&table->philo[i]);
				return ;
			}
			i++;
		}
		if (check_total_meals(table->philo))
			break ;
		usleep(100);
	}
}

void	clean_up(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			printf("Error : Failed to join thread %d\n", i);
		i++;
	}
	i = 0;
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
