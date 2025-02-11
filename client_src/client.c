/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:12:44 by lucmansa          #+#    #+#             */
/*   Updated: 2025/02/11 17:06:27 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/utils.h"

int	g_reception = 0;

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nbr = nbr * 10 + (nptr[i++] - '0');
	return (nbr);
}

void	ft_tobin(unsigned char i, int pid)
{
	int	t;
	int	j;

	j = 8;
	while (--j >= 0)
	{
		if ((i >> j) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		t = 0;
		while (g_reception != 1)
		{
			if (t == 500)
			{
				j++;
				g_reception = 1;
			}
			t++;
			usleep(1);
		}
		t = 0;
		g_reception = 0;
	}
}

void	ft_signal(int sig)
{
	if (sig == SIGUSR2)
		g_reception = 1;
	else if (sig == SIGUSR1)
		ft_putstr(1, "reception OK");
	exit(0);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	signal(SIGUSR1, ft_signal);
	signal(SIGUSR2, ft_signal);
	if (argc < 3)
		return (ft_putstr(2, "Error"), 1);
	pid = ft_atoi(argv[1]);
	i = -1;
	while (argv[2][++i])
		ft_tobin(argv[2][i], pid);
	ft_tobin('\0', pid);
	while (1)
		;
	return (0);
}
