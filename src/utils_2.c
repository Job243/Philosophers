/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:53:15 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/10 23:13:10 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_total_meals(t_philosopher *philo)
{
	int	i;

	i = 1;
	while (i != philo->table->philo_nbr)
	{
		if (philo->meals_eaten == philo->table->total_meals)
			i++;
		else
			break ;
	}
	if (i == philo->table->philo_nbr)
		{
			free(philo->table);
			free(philo);
			printf("tout les philo on manger : merci\n");
			exit(1);
		}
}
