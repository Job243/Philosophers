/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:17:28 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/13 21:13:13 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_error(const char *msg)
{
	printf(RED "%s\n" RST, msg);
	exit(EXIT_FAILURE);
}

bool	print_action(t_philosopher *philo, const char *action)
{
	size_t	timestamp;
	size_t	start;

	start = philo->table->start_time;
	timestamp = get_time();
	pthread_mutex_lock(&philo->table->print_mutex);
	if (is_alive(philo) == 0)
		return (pthread_mutex_unlock(&philo->table->print_mutex), true);
	printf(G"%ld %d %s\n"RST, timestamp - start, philo->id, action);
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (false);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(int milliseconds, t_philosopher *philo)
{
	long	begin;

	begin = get_time();
	while (get_time() - begin < milliseconds)
	{
		if (is_alive(philo) == 0)
			return (0);
		usleep(800);
	}
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
