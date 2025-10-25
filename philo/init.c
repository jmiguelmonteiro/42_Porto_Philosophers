/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:01:35 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/25 19:10:03 by josemigu         ###   ########.fr       */
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

	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->philos)
	{
		ft_putstr("Error: Memory allocation for philosophers failed.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal_ms = get_time();
		table->philos[i].meals_eaten = 0;
		table->philos[i].right_fork = &table->philos[right_philo_index(i, table->nb_philos)].left_fork;
		table->philos[i].table = table;
		if ((pthread_mutex_init(&table->philos[i].left_fork, NULL) != 0) ||
		   (pthread_mutex_init(&table->philos[i++].last_meal_mutex, NULL) != 0))
		{
			ft_putstr("Error: Philosophers mutex initialization failed.\n");
			free(table->philos);
			exit(EXIT_FAILURE);
		}
	}
}

static void	init_table(t_table *table, int argc, char *argv[])
{
	table->nb_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5]);
	else
		table->meals_required = -1;
	table->simulation_running = true;
	table->someone_died = false;
	if ((pthread_mutex_init(&table->print_mutex, NULL) != 0) ||
		(pthread_mutex_init(&table->someone_died_mutex, NULL) != 0))
	{
		ft_putstr("Error: Table mnutex initialization failed.\n");
		exit(EXIT_FAILURE);
	}
}	

void	init_data(t_table *table, int argc, char *argv[])
{
	init_table(table, argc, argv);
	init_philosophers(table);
}
