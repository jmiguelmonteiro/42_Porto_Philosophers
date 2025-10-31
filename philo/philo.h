/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:13:39 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/31 15:48:42 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	long		last_meal_ms;
	t_mutex		last_meal_mutex;
	int			meals_eaten;
	t_mutex		meals_eaten_mutex;
	bool		left_fork;
	t_mutex		l_fork_mutex;
	bool		*right_fork;
	t_mutex		*r_fork_mutex;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int			nb_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_required;
	bool		someone_died;
	t_mutex		someone_died_mutex;
	long		min_last_meal;
	t_mutex		min_last_meal_mutex;
	t_mutex		print_mutex;
	pthread_t	monitor_thread;
	t_philo		*philos;
}	t_table;

void	init_data(t_table *table, int argc, char *argv[]);
int		simulation(t_table *table);
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);

long	get_time(void);
bool	get_someone_died(t_table *table);
void	set_someone_died(t_table *table, t_philo *philo);
long	get_last_meal(t_philo *philo);
void	set_last_meal(t_philo *philo, long timestamp);
long	get_min_last_meal(t_table *table);
void	set_min_last_meal(t_table *table, long value);
int		get_meals_eaten(t_philo *philo);
void	increment_meals_eaten(t_philo *philo);

void	lock_fork(t_philo *philo, t_mutex *fork);
void	lock_forks(t_philo *philo, t_table *table);
void	unlock_forks(t_philo *philo);
bool	try_lock_forks(t_philo *philo);

bool	check_arg_is_int(char *nptr);
int		ft_atoi(char *str);
void	free_data(t_table *table);
void	print_status(t_philo *philo, char *msg);
void	msleep(long ms, t_table *table);

int		init_mutexes(t_table *table);
void	destroy_mutexes(t_table *table);

#endif
