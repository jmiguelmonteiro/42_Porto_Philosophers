/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:27:09 by josemigu          #+#    #+#             */
/*   Updated: 2025/07/11 18:42:10 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	printf("atoi: %d\n", ft_atoi(argv[1]));
	if (argc < 5 || argc > 6)
	{
		ft_putstr("Usage: ./philo number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
