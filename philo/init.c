/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:01:35 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/23 14:01:35 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(t_table *table)
{
	int		i;

	table->philosophers = malloc(sizeof(t_philo) * table->nb_philosophers);
	if (!table->philosophers)
	{
		ft_putstr("Error: Memory allocation for philosophers failed.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < table->nb_philosophers)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].meals_eaten = 0;
		i++;
	}
}
void	init_table(t_table *table, int argc, char *argv[])
{
	table->nb_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5]);
	else
		table->meals_required = -1;
	table->simulation_running = true;
}	
