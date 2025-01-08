/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:12:38 by lucmansa          #+#    #+#             */
/*   Updated: 2025/01/08 17:52:44 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "utils.h"

int message[3] = {0, 0, 0};

void on_signal(int signal, siginfo_t *info, void *context)
{
    (void)context;
    if (signal == SIGUSR1)
    {
        message[0] <<= 1;
        message[0] |= 1;
    }
    else if (signal == SIGUSR2)
        message[0] <<= 1;
    message[1]++;
    message[2] = info->si_pid;
}

void header()
{
    int pid;

    pid  = getpid();
    ft_putnbr(pid);
    ft_putchar('\n');
}

int main()
{
    struct sigaction	action;

    header();
    action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = on_signal;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
    while (1)
    {
        if (message[1] == 8)
        {
            if (message[0] == 0)
                kill(message[2], SIGUSR1);
            else
                write(1, &message[0], 1);
            message[0] = 0;
            message[1] = 0;
        }
        pause();
    }
}
