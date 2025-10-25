/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:31:44 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/25 22:34:41 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void msleep(long ms)
{
    long start = get_time();
    while (get_time() - start < ms)
        usleep(100);
}

void print_status(t_philo *philo, char *msg, long timestamp)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	lock_forks(t_philo *philo, t_table *table)
{
	if (philo->id < ((philo->id + 1) % table->nb_philos))
	{
		pthread_mutex_lock(&philo->left_fork);
		print_status(philo, "has taken a fork", get_time());
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork", get_time());
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork", get_time());
		pthread_mutex_lock(&philo->left_fork);
		print_status(philo, "has taken a fork", get_time());
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

int	eating(t_philo *philo, t_table *table)
{
	long	timestamp;

	if (get_someone_died(table))
		return (EXIT_FAILURE);
	lock_forks(philo, table);
	if (get_someone_died(table))
		return (unlock_forks(philo), EXIT_FAILURE);
	timestamp = get_time();
	print_status(philo, "is eating", timestamp);
	set_last_meal(philo, timestamp);
	msleep(table->time_to_eat);
	unlock_forks(philo);
	philo->meals_eaten++;
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *philo, t_table *table)
{
	if (get_someone_died(table))
		return (EXIT_FAILURE);
	print_status(philo, "is sleeping", get_time());
	msleep(table->time_to_sleep);
	return (EXIT_SUCCESS);
}

int	thinking(t_philo *philo, t_table *table)
{
	if (get_someone_died(table))
		return (EXIT_FAILURE);
	print_status(philo, "is thinking", get_time());
	return (EXIT_SUCCESS);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_table *table = philo->table;

	while (get_simulation_running(table) && !get_someone_died(table))
	{
		if (eating(philo, table) == EXIT_FAILURE)
			break ;
		if ((table->meals_required != -1) && (philo->meals_eaten >= table->meals_required))
		{
			set_simulation_running(table, false);
			break ;
		}
		if (sleeping(philo, table) == EXIT_FAILURE)
			break ;
		if (thinking(philo, table) == EXIT_FAILURE)
			break ;
	}
	return (NULL);
}

int simulation(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philosopher_routine, &table->philos[i]) != 0)
		{
			ft_putstr("Error: Failed to create philosopher thread.\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_create(&table->monitor_thread, NULL, monitor_routine, table) != 0)
	{
		ft_putstr("Error: Failed to create monitor thread.\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < table->nb_philos)
		pthread_join(table->philos[i++].thread, NULL);
	pthread_join(table->monitor_thread, NULL);
	// i = 0;	
	// while (i < table->nb_philosophers)
	// 	pthread_detach(table->philosophers[i++].thread);
	// pthread_detach(table->monitor_thread);
	return (EXIT_SUCCESS);
}
