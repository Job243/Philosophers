/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:13:36 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/13 22:48:43 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo->table->philo_nbr == 1)
			return (one_philo_handler(philo->table), NULL);
		if (philo->table->philo_nbr % 2)
			ft_usleep(philo->table->time_to_sleep * 0.25, philo);
		if (eat(philo) == 0)
			break ;
		if (sleep_philo(philo) == 0)
			break ;
		if (think(philo) == 0)
			break ;
	}
	return (0);
}

int	sleep_philo(t_philosopher *philo)
{
	print_action(philo, B"is sleeping"RST);
	return (ft_usleep(philo->table->time_to_sleep, philo));
}

int	think(t_philosopher *philo)
{
	if (print_action(philo, BLUE"is thinking"RST) == true)
		return (0);
	return (1);
}

void	one_philo_handler(t_table *table)
{
	print_action(table->philo, M"has taken a fork"RST);
	usleep(table->time_to_die * 1000);
	return ;
}
