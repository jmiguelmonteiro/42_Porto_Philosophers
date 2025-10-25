/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:37:49 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/25 19:23:09 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_someone_died(t_table *table)
{
	pthread_mutex_lock(&table->someone_died_mutex);
	table->someone_died = true;
	pthread_mutex_unlock(&table->someone_died_mutex);
}

long	get_last_meal(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal = philo->last_meal_ms;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (last_meal);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	long	current_time;
	long	last_meal;

	table = (t_table *)arg;
	while (table->simulation_running)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			current_time = get_time();
			last_meal = get_last_meal(&table->philos[i]);
			if (current_time - last_meal > table->time_to_die)
			{
				print_status(&table->philos[i], "died", current_time);
				set_someone_died(table);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
