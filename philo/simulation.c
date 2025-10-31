/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:31:44 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/31 14:50:16 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo, t_table *table)
{
	if (philo->id % 2 == 0)
		usleep(100);
	while ((get_min_last_meal(table) != get_last_meal(philo))
		&& (get_min_last_meal(table) != 0) && !get_someone_died(table))
		usleep(1);
	if (get_someone_died(table))
		return (EXIT_FAILURE);
	while (!try_lock_forks(philo))
	{
		if (get_someone_died(table))
			return (EXIT_FAILURE);
		usleep(1);
	}
	if (get_someone_died(table))
	{
		unlock_forks(philo);
		return (EXIT_FAILURE);
	}
	increment_meals_eaten(philo);
	set_last_meal(philo, get_time());
	print_status(philo, "is eating");
	msleep(table->time_to_eat, table);
	unlock_forks(philo);
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *philo, t_table *table)
{
	if (get_someone_died(table))
		return (EXIT_FAILURE);
	print_status(philo, "is sleeping");
	msleep(table->time_to_sleep, table);
	return (EXIT_SUCCESS);
}

int	thinking(t_philo *philo, t_table *table)
{
	if (get_someone_died(table))
		return (EXIT_FAILURE);
	print_status(philo, "is thinking");
	return (EXIT_SUCCESS);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nb_philos == 1)
	{
		print_status(philo, "has taken a fork");
		msleep(philo->table->time_to_die, philo->table);
	}
	else
	{
		while (!get_someone_died(philo->table))
		{
			if (thinking(philo, philo->table) == EXIT_FAILURE)
				return (NULL);
			if (eating(philo, philo->table) == EXIT_FAILURE)
				return (NULL);
			if ((philo->table->meals_required != -1)
				&& (get_meals_eaten(philo) >= philo->table->meals_required))
				return (NULL);
			if (sleeping(philo, philo->table) == EXIT_FAILURE)
				return (NULL);
			usleep(1);
		}
	}
	return (NULL);
}

int	simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philosopher_routine,
				&table->philos[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread.\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_create(&table->monitor_thread, NULL, monitor_routine, table)
		!= 0)
	{
		printf("Error: Failed to create monitor thread.\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < table->nb_philos)
		pthread_join(table->philos[i++].thread, NULL);
	pthread_join(table->monitor_thread, NULL);
	return (EXIT_SUCCESS);
}
