/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:29:22 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/30 19:43:49 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_arg_is_int(char *nptr)
{
	long	value;
	int		signal;

	value = 0;
	signal = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal = -1;
		nptr++;
		if (*nptr < '0' || *nptr > '9')
			return (false);
	}
	while (*nptr)
	{
		if (*nptr >= '0' && *nptr <= '9')
			value = value * 10 + *nptr++ - '0';
		else
			return (false);
		if (((value * signal) > INT_MAX) || ((value * signal) < INT_MIN))
			return (false);
	}
	return (true);
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

void	free_data(t_table *table)
{
	destroy_mutexes(table);
	if (table->philos)
		free(table->philos);
}

void	print_status(t_philo *philo, char *msg, long timestamp)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (get_someone_died(philo->table))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
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
