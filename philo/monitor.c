/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:37:49 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/26 13:01:17 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_philos_finished(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (table->meals_required == -1 || table->philos[i].meals_eaten
			< table->meals_required)
			return (false);
		i++;
	}
	return (true);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	long	last_meal;

	table = (t_table *)arg;
	while (true)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (table->meals_required != -1 && table->philos[i].meals_eaten
				>= table->meals_required)
			{
				i++;
				continue ;
			}
			last_meal = get_last_meal(&table->philos[i++]);
			if (get_time() - last_meal > table->time_to_die)
				return (set_someone_died(table, &table->philos[i - 1]), NULL);
		}
		if (all_philos_finished(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
