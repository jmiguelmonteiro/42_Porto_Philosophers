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

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	long	current_time;
	long	last_meal;

	table = (t_table *)arg;
	while (get_simulation_running(table))
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
				set_simulation_running(table, false);
				
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
