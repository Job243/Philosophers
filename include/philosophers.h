/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:08:59 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/07 20:53:00 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

typedef struct s_philosopher
{
	int		id;
	int		meals_eaten;
	long long	last_meal;
	pthread_t	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}	t_philosopher;

typedef struct s_table
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_meals;
	int				all_alive;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output_mutex;
	t_philosopher	*philo;
}	t_table;

#endif
