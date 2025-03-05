/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:12:38 by lucmansa          #+#    #+#             */
/*   Updated: 2025/03/05 19:22:42 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	g_message[4] = {0, 0, 0, 0};
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
	if (g_message[1] < 8)
		kill(g_message[2], SIGUSR2);
}

void	header(void)
{
	int	pid;
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = on_signal;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	pid = getpid();
	ft_putnbr(pid);
	ft_putchar('\n');
}

void	ft_reset(char **res)
{
	g_message[3] = -1;
	ft_putstr(1, *res);
	free(*res);
	*res = NULL;
	kill(g_message[2], SIGUSR1);
}
int	main(void)
{
	char *res;

	header();
	res = NULL;
	while (1)
	{
		if (g_message[1] >= 8)
		{
			res = ft_realloc(res, g_message[3], g_message[3] + 1);
			if (!res)
				return (1);
			res[g_message[3]] = g_message[0];
			if (g_message[0] == 0)
				ft_reset(&res);
			g_message[0] = 0;
			g_message[1] = 0;
			g_message[3]++;
			kill(g_message[2], SIGUSR2);
		}
		pause();
	}
}
