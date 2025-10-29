/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:13:52 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/29 14:42:39 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_philo *philo, t_mutex *fork)
{
	pthread_mutex_lock(fork);
	check_print_status(philo, "has taken a fork", get_time());
}

void	lock_forks(t_philo *philo, t_table *table)
{
	(void)table;
	if (philo->id % 2 == 0)
	{
		lock_fork(philo, &philo->left_fork);
		lock_fork(philo, philo->right_fork);
	}
	else
	{
		lock_fork(philo, philo->right_fork);
		lock_fork(philo, &philo->left_fork);
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	unlock_all_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_unlock(&table->philos[i].left_fork);
		i++;
	}
}
