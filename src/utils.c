/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:17:28 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/01 18:37:33 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

#include <stdbool.h>

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
	if (full)
	{
		pthread_mutex_lock(&philo->table->all_alive_mutex);
		philo->table->all_alive = 0;
		pthread_mutex_unlock(&philo->table->all_alive_mutex);
		// usleep(100);
		printf(BLUE "All philosophers have eaten" RST
			BLUE " the required number of meals!\n" RST);
	}
	return (full);
}



void	print_action(t_philosopher *philo, const char *action)
{
	size_t		timestamp;
	size_t			start;

	start = philo->table->start_time;
	timestamp = get_time();
	pthread_mutex_lock(&philo->table->print_mutex);
	printf(G "%ld %d %s\n" RST, timestamp - start, philo->id, action);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_error(const char *msg)
{
	printf(RED "%s\n" RST, msg);
	exit(EXIT_FAILURE);
}

int	ft_usleep(size_t milliseconds, t_philosopher *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&philo->table->all_alive_mutex);
		if (philo->table->all_alive == 0)
		{
			pthread_mutex_unlock(&philo->table->all_alive_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->table->all_alive_mutex);

		pthread_mutex_lock(&philo->meal_mutex);
		if (check_total_meals(philo) == 1)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		usleep(10);
	}
	return (0);
}
