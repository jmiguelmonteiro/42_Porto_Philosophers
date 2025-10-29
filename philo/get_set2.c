/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:19:43 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/29 18:03:07 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_min_last_meal(t_table *table)
{
	long	min_last_meal;

	pthread_mutex_lock(&table->min_last_meal_mutex);
	min_last_meal = table->min_last_meal;
	pthread_mutex_unlock(&table->min_last_meal_mutex);
	return (min_last_meal);
}

void	set_min_last_meal(t_table *table, long value)
{
	pthread_mutex_lock(&table->min_last_meal_mutex);
	table->min_last_meal = value;
	pthread_mutex_unlock(&table->min_last_meal_mutex);
}

int	get_meals_eaten(t_philo *philo)
{
	int	meals_eaten;

	pthread_mutex_lock(&philo->meals_eaten_mutex);
	meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	return (meals_eaten);
}

void	increment_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
}
