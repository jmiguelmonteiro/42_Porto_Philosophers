/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:29:22 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/29 17:31:11 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	free_data(t_table *table)
{
	destroy_mutexes(table);
	if (table->philos)
		free(table->philos);
}

void	print_status(t_philo *philo, char *msg, long timestamp)
{
	if (get_someone_died(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	msleep(long ms, t_table *table)
{
	long	start;

	(void)table;
	start = get_time();
	while (get_time() - start < ms)
	{
		if (get_someone_died(table))
			break ;
		usleep(500);
	}
}
