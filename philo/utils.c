/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:29:22 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/25 22:18:37 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_atoi(char *str)
{
	unsigned int	value;
	int				signal;

	signal = 1;
	value = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signal = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		value = value * 10 + *str++ - '0';
	return (signal * value);
}

void	free_table(t_table *table)
{
	int	i;
	
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->philos[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->simulation_mutex);
	pthread_mutex_destroy(&table->someone_died_mutex);
	if (table->philos)
		free(table->philos);
}
