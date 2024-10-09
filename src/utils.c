/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:17:28 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/09 22:11:33 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_philos(t_table *table)
{
	int		i;

	while (table->all_alive)
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			pthread_mutex_lock(&table->philo[i].meal_mutex);
			if (get_time() - table->philo[i].last_meal > table->time_to_die)
			{
				pthread_mutex_lock(&table->all_alive_mutex);
				table->all_alive = 0;
				pthread_mutex_unlock(&table->all_alive_mutex);
				pthread_mutex_unlock(&table->philo[i].meal_mutex);
				usleep(10);
				print_action(table->philo[i].id, " died");
				return ;
			}
			pthread_mutex_unlock(&table->philo[i].meal_mutex);
			i++;
		}
		usleep(10000);
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
	printf("[%ld] Philosopher %d %s\n", timestamp, philo_id, action);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
