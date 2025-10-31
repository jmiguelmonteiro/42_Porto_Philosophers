/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:13:52 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/31 15:49:47 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	lock_fork(t_philo *philo, t_mutex *fork)
// {
// 	pthread_mutex_lock(fork);
// 	print_status(philo, "has taken a fork", get_time());
// }

// void	lock_forks(t_philo *philo, t_table *table)
// {
// 	(void)table;
// 	if (philo->id % 2 == 0)
// 	{
// 		lock_fork(philo, &philo->left_fork);
// 		lock_fork(philo, philo->right_fork);
// 	}
// 	else
// 	{
// 		lock_fork(philo, philo->right_fork);
// 		lock_fork(philo, &philo->left_fork);
// 	}
// }

void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork_mutex);
		pthread_mutex_lock(&philo->l_fork_mutex);
		philo->left_fork = false;
		*(philo->right_fork) = false;
		pthread_mutex_unlock(&philo->l_fork_mutex);
		pthread_mutex_unlock(philo->r_fork_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork_mutex);
		pthread_mutex_lock(philo->r_fork_mutex);
		philo->left_fork = false;
		*(philo->right_fork) = false;
		pthread_mutex_unlock(philo->r_fork_mutex);
		pthread_mutex_unlock(&philo->l_fork_mutex);
	}
}

bool	try_lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork_mutex);
		if (*(philo->right_fork) == false)
		{
			pthread_mutex_lock(&philo->l_fork_mutex);
			if (philo->left_fork == false)
			{
				philo->left_fork = true;
				*(philo->right_fork) = true;
				print_status(philo, "has taken a fork");
				print_status(philo, "has taken a fork");
				pthread_mutex_unlock(&philo->l_fork_mutex);
				pthread_mutex_unlock(philo->r_fork_mutex);
				return (true);
			}
			pthread_mutex_unlock(&philo->l_fork_mutex);
		}
		pthread_mutex_unlock(philo->r_fork_mutex);
		return (false);
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork_mutex);
		if (philo->left_fork == false)
		{
			pthread_mutex_lock(philo->r_fork_mutex);
			if (*(philo->right_fork) == false)
			{
				philo->left_fork = true;
				*(philo->right_fork) = true;
				print_status(philo, "has taken a fork");
				print_status(philo, "has taken a fork");
				pthread_mutex_unlock(philo->r_fork_mutex);
				pthread_mutex_unlock(&philo->l_fork_mutex);
				return (true);
			}
			pthread_mutex_unlock(philo->r_fork_mutex);
		}
		pthread_mutex_unlock(&philo->l_fork_mutex);
		return (false);
	}
}
