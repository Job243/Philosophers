/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:08:59 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/09 21:43:32 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t meal_mutex;
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
	pthread_mutex_t all_alive_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output_mutex;
	t_philosopher	*philo;
}	t_table;

void	assign_philo_number(t_table *table);
void	check_philos(t_table *table);
void	created_threads(t_table *table);
long	get_time(void);
void	init_philosophers(t_table *table);
void	join_threads(t_table *table);
void	print_action(int philo_id, const char *action);
void	start_simulation(t_table *table);
void	*philosopher_routine(void *arg);

#endif
