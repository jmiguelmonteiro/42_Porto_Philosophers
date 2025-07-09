/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:29:22 by josemigu          #+#    #+#             */
/*   Updated: 2025/07/09 18:32:23 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[0])
		i++;
	return i;
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}
