/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:13:39 by josemigu          #+#    #+#             */
/*   Updated: 2025/07/11 18:32:50 by josemigu         ###   ########.fr       */
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

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING,
	DEAD
}	t_state;

typedef struct	s_philo {
	int			id;
	long		last_meal_time;
	int			meals_eaten;
	t_state		state;
	pthread_t	thread;
	t_mutex		left_fork;
	t_mutex		*right_fork;
	t_table		*table;
}	t_philo;

typedef struct	s_table
{
	int		nb_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_required;
	bool	simulation_running;
	t_philo	*philosophers;
	t_mutex	print_mutex;
}	t_table;

void	init_table(t_table *table, int argc, char *argv[]);
void	init_philosophers(t_table *table);
void	start_simulation(t_table *table);

int		ft_strlen(char *str);
void	ft_putstr(char *str);
int		ft_atoi(char *str);
void	free_table(t_table *table);

#endif
