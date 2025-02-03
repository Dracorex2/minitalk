/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:12:44 by lucmansa          #+#    #+#             */
/*   Updated: 2025/02/03 11:17:15 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

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
	int	j;

	j = 8;
	while (--j >= 0)
	{
		if ((i >> j) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
	}
}

void	ft_signal(int sig)
{
	(void)sig;
	ft_putstr(1, "send ok");
	exit(0);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	signal(SIGUSR1, ft_signal);
	if (argc < 2)
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
