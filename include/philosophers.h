/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:08:59 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/10 23:21:27 by jmafueni         ###   ########.fr       */
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
# include <limits.h>

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

int					is_space(char c);
int					is_digit(int c);
const char			*valid_input(const char *str);
void				assign_philo_number(t_table *table);
void				check_philos(t_table *table);
void				check_total_meals(t_philosopher *philo);
void				created_threads(t_table *table);
void				eat(t_philosopher *philo);
long				ft_atol(const char *str);
long				get_time(void);
void				init_philosophers(t_table *table);
void				join_threads(t_table *table);
void				print_action(int philo_id, const char *action);
void				release_forks(t_philosopher *philo);
void				sleep_philo(t_philosopher *philo);
void				take_forks(t_philosopher *philo);
void				start_simulation(t_table *table);
void				think(t_philosopher *philo);
void				*philosopher_routine(void *arg);

#endif
