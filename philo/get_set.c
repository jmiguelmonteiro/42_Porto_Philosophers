/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:57:53 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/29 16:20:04 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

bool	get_someone_died(t_table *table)
{
	bool	someone_died;

	pthread_mutex_lock(&table->someone_died_mutex);
	someone_died = table->someone_died;
	pthread_mutex_unlock(&table->someone_died_mutex);
	return (someone_died);
}

void	set_someone_died(t_table *table, t_philo *philo)
{
	print_status(philo, "died", get_time());
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

void	set_last_meal(t_philo *philo, long timestamp)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_ms = timestamp;
	pthread_mutex_unlock(&philo->last_meal_mutex);
}
