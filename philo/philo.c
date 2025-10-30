/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:27:09 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/25 18:09:57 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Invalid input.\n\nUsage: ./philo number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
		exit(EXIT_FAILURE);
	}
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Invalid input: All arguments must be positive integers.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_table	table;

	check_args(argc, argv);
	init_data(&table, argc, argv);
	simulation(&table);
	free_data(&table);
	return (EXIT_SUCCESS);
}
