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

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;

typedef struct	s_philo {
	int			id;
	long		last_meal_time;
	int			meals_eaten;
	pthread_t	thread;
	t_mutex		*fork;
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
}	t_table;

void	init_table(t_table *table, int argc, char *argv[]);
void	init_philosophers(t_table *table);

int		ft_strlen(char *str);
void	ft_putstr(char *str);
int		ft_atoi(char *str);
void	free_table(t_table *table);

#endif
