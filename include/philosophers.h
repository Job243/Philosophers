/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:08:59 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/31 20:41:57 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define RST "\033[0m"    /* Reset the color by default color*/
# define B "\e[1;90m"     /*Black*/
# define RED "\033[1;31m" /*Red*/
# define G "\e[1;92m"     /*Green*/
# define Y "\e[1;93m"     /*Yellow*/
# define BLUE "\e[1;94m"  /*Blue*/
# define M "\e[1;95m"     /*Magenta*/
# define C "\e[1;96m"     /*Cyan*/
# define W "\e[1;97m"     /*White*/

typedef pthread_mutex_t t_mtx;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t ph_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_time;
	struct s_table	*table;
}					t_philosopher;

typedef struct s_table
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_meals;
	int				all_alive;
	long			start_time;
	pthread_mutex_t	all_alive_mutex;
	pthread_mutex_t	print_mutex;
	t_philosopher	*philo;
}					t_table;

int					check_n_handle_death(t_philosopher *philo);
int					check_total_meals(t_philosopher *philo);
int					is_alive(t_philosopher *philo);
int					is_space(char c);
int					is_digit(int c);
int					ft_usleep(size_t milliseconds, t_philosopher *philo);

const char			*valid_input(const char *str);
int				check_philos(t_table *table);
void				clean_up(t_table *table);
void				created_threads(t_table *table);
// void				eat(t_philosopher *philo);
long				ft_atol(const char *str);
void				ft_error(const char *msg);
long				get_time(void);
void				init_philosophers(t_table *table);
void				join_threads(t_table *table);
void				print_action(t_philosopher *philo, const char *action);
// void				release_forks(t_philosopher *philo);
// void				sleep_philo(t_philosopher *philo);
// void				take_forks(t_philosopher *philo);
void				start_simulation(t_table *table);
// void				think_n_sleep(t_philosopher *philo);
void				*philosopher_routine(void *arg);

int					eat(t_philosopher *philo);
int					sleep_philo(t_philosopher *philo);
int					take_forks_even(t_philosopher *philo);
int					take_forks_odd(t_philosopher *philo);
int					think(t_philosopher *philo);
int					valid_arg(int ac, char **av);


#endif
