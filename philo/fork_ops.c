/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:13:52 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/31 17:24:13 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static bool	try_lock_forks_right_first(t_philo *philo)
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

static bool	try_lock_forks_left_first(t_philo *philo)
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

bool	try_lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (try_lock_forks_right_first(philo));
	else
		return (try_lock_forks_left_first(philo));
}
