/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:12:38 by lucmansa          #+#    #+#             */
/*   Updated: 2025/03/05 10:34:26 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"

int	g_message[3] = {0, 0, 0};
//char, nb_bits, pid, str_size
void	on_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (signal == SIGUSR2)
	{
		g_message[0] <<= 1;
		g_message[0] |= 1;
	}
	else if (signal == SIGUSR1)
		g_message[0] <<= 1;
	g_message[1]++;
	g_message[2] = info->si_pid;
	kill(g_message[2], SIGUSR2);
}

void	header(void)
{
	int	pid;

	pid = getpid();
	ft_putnbr(pid);
	ft_putchar('\n');
}

int	main(void)
{
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = on_signal;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	header();
	while (1)
	{
		if (g_message[1] == 8)
		{
			if (g_message[0] == 0)
			{
				g_message[0] = 0;
				g_message[1] = 0;
				kill(g_message[2], SIGUSR1);
			}
			write(1, &g_message[0], 1);
			g_message[0] = 0;
			g_message[1] = 0;
		}
		pause();
	}
}
