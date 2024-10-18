/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:17:28 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/15 18:37:30 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_total_meals(t_philosopher *philo)
{
	int	i;
	int	full;

	i = 0;
	full = 1;
	while (i < philo->table->philo_nbr)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (philo->meals_eaten < philo->table->total_meals)
			full = 0;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	if (full)
	{
		pthread_mutex_lock(&philo->table->all_alive_mutex);
		philo->table->all_alive = 0;
		pthread_mutex_unlock(&philo->table->all_alive_mutex);
		clean_up(philo->table);
		printf("All philosophers have eaten the required number of meals!\n");
		exit(0);
	}
}

void	assign_philo_number(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philo[i].id = i + 1;
		i++;
	}
}

void	print_action(int philo_id, const char *action)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf(G"[%ld] Philosopher %d %s\n"RST, timestamp, philo_id, action);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_error(const char *msg)
{
	printf(RED"%s\n"RST, msg);
	exit(EXIT_FAILURE);
}
