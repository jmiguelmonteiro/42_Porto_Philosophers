/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:31:44 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/25 19:27:08 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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

void	set_last_meal(t_philo *philo, long timestamp)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_ms = timestamp;
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

int	eating(t_philo *philo)
{
	t_table *table;
	long	timestamp;

	table = philo->table;
	if (table->someone_died)
		return (EXIT_FAILURE);
	if (philo->id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&philo->left_fork);
	print_status(philo, "has taken a fork", get_time());
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork", get_time());
	if (table->someone_died)
		return (EXIT_FAILURE);
	timestamp = get_time();
	print_status(philo, "is eating", timestamp);
	set_last_meal(philo, timestamp);
	msleep(table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	philo->meals_eaten++;
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (table->someone_died)
		return (EXIT_FAILURE);
	print_status(philo, "is sleeping", get_time());
	msleep(table->time_to_sleep);
	return (EXIT_SUCCESS);
}

int	thinking(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (table->someone_died)
		return (EXIT_FAILURE);
	print_status(philo, "is thinking", get_time());
	return (EXIT_SUCCESS);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_table *table = philo->table;

	while (table->simulation_running && !table->someone_died)
	{
		if ((table->meals_required != -1) && (philo->meals_eaten >= table->meals_required))
			break ;
		if (eating(philo) == EXIT_FAILURE)
			break ;
		if (sleeping(philo) == EXIT_FAILURE)
			break ;
		if (thinking(philo) == EXIT_FAILURE)
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
