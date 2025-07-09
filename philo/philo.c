/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:27:09 by josemigu          #+#    #+#             */
/*   Updated: 2025/07/09 15:28:57 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		ft_printf("Usage: ./client server_pid string_to_send\n");
		return (EXIT_FAILURE);
	}
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = signal_handler_client;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if ((sigaction(SIGUSR1, &sa, NULL) == -1)
		|| (sigaction(SIGUSR2, &sa, NULL) == -1))
	{
		ft_printf("Client: Error changing signals action.\n");
		return (EXIT_FAILURE);
	}
	ft_printf("Client: Sending message.\n");
	send_string(ft_atoi(argv[1]), argv[2]);
	return (EXIT_SUCCESS);
}
