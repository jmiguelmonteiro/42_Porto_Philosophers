/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:37:49 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/29 18:48:26 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static bool	all_philos_finished(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (table->meals_required == -1 || get_meals_eaten(&table->philos[i])
			< table->meals_required)
			return (false);
		i++;
	}
	return (true);
}

static void	monitor_loop(t_table *table, int i, long last_meal,
	long min_last_meal)
{
	while (true)
	{
		i = 0;
		min_last_meal = LONG_MAX;
		while (i < table->nb_philos)
		{
			if (table->meals_required != -1
				&& get_meals_eaten(&table->philos[i]) >= table->meals_required)
			{
				i++;
				continue ;
			}
			last_meal = get_last_meal(&table->philos[i++]);
			if (get_time() - last_meal > table->time_to_die)
				return (set_someone_died(table, &table->philos[i - 1]));
			if (last_meal < min_last_meal)
				min_last_meal = last_meal;
		}
		if (all_philos_finished(table))
			return ;
		set_min_last_meal(table, min_last_meal);
		usleep(1);
	}
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	monitor_loop(table, 0, 0, 0);
	return (NULL);
}
