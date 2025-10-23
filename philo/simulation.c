/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:31:44 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/23 16:31:44 by josemigu         ###   ########.fr       */
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

void print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d %s\n", get_time(), philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_table *table = philo->table;

	while (table->simulation_running)
	{
		pthread_mutex_lock(&philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		msleep(table->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		philo->meals_eaten++;
		philo->last_meal_time = get_time();
		print_status(philo, "is sleeping");
		msleep(table->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nb_philosophers)
	{
		pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < table->nb_philosophers)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
}
