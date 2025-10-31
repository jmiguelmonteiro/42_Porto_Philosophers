/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:13:52 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/31 13:13:14 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_philo *philo, t_mutex *fork)
{
	pthread_mutex_lock(fork);
	print_status(philo, "has taken a fork", get_time());
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

// bool	try_lock_forks(t_philo *philo, t_table *table)
// {
// 	int	one_available;
// 	int	ret;

// 	pthread_mutex_lock(&philo->fork_mutex);
// 	if (philo->fork == -1)
// 	{
// 		pthread_mutex_unlock(&philo->fork_mutex);
// 		return (true);
// 	}

	
// 	if (pthread_mutex_trylock(&philo->left_fork) == 0)
// 	{
// 		print_status(philo, "has taken a fork", get_time());
// 		if (pthread_mutex_trylock(philo->right_fork) == 0)
// 		{
// 			print_status(philo, "has taken a fork", get_time());
// 			return (EXIT_SUCCESS);
// 		}
// 		else
// 		{
// 			pthread_mutex_unlock(&philo->left_fork);
// 		}
// 	}
// 	return (EXIT_FAILURE);
// }
