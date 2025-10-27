/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:13:39 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/26 12:27:45 by josemigu         ###   ########.fr       */
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

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;

typedef struct	s_philo {
	int			id;
	pthread_t	thread;
	long		last_meal_ms;
	t_mutex		last_meal_mutex;
	int			meals_eaten;
	t_mutex		left_fork;
	t_mutex		*right_fork;
	t_table		*table;
}	t_philo;

typedef struct	s_table
{
	int			nb_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_required;
	bool		someone_died;
	t_mutex		someone_died_mutex;
	pthread_t	monitor_thread;
	t_philo		*philos;
	t_mutex		print_mutex;
}	t_table;

void	init_data(t_table *table, int argc, char *argv[]);
int		simulation(t_table *table);
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);
void	msleep(long ms);
void	print_status(t_philo *philo, char *msg, long timestamp);

long	get_time(void);
bool	get_simulation_running(t_table *table);
void	set_simulation_running(t_table *table, bool running);
bool	get_someone_died(t_table *table);
void	set_someone_died(t_table *table);
long	get_last_meal(t_philo *philo);
void	set_last_meal(t_philo *philo, long timestamp);

int		ft_strlen(char *str);
void	ft_putstr(char *str);
int		ft_atoi(char *str);
void	free_table(t_table *table);

#endif
