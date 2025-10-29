/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:01:35 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/29 17:59:07 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	right_philo_index(int i, int nb_philosophers)
{
	if (i == nb_philosophers - 1)
		return (0);
	else
		return (i + 1);
}

static void	init_philosophers(t_table *table)
{
	int		i;
	long	current_time;

	current_time = get_time();
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->philos)
	{
		printf("Error: Memory allocation for philosophers failed.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < table->nb_philos)
	{
		memset(&table->philos[i], 0, sizeof(t_philo));
		table->philos[i].id = i + 1;
		table->philos[i].last_meal_ms = current_time;
		table->philos[i].meals_eaten = 0;
		table->philos[i].right_fork
			= &table->philos[right_philo_index(i, table->nb_philos)].left_fork;
		table->philos[i].table = table;
		i++;
	}
}

static void	init_table(t_table *table, int argc, char *argv[])
{
	memset(table, 0, sizeof(t_table));
	table->nb_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5]);
	else
		table->meals_required = -1;
	table->someone_died = false;
	table->min_last_meal = 0;
}

void	init_data(t_table *table, int argc, char *argv[])
{
	init_table(table, argc, argv);
	init_philosophers(table);
	if (init_mutexes(table) != EXIT_SUCCESS)
	{
		printf("Error: Mutex initialization failed.\n");
		free_data(table);
		exit(EXIT_FAILURE);
	}
}
