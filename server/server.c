#include <signal.h>
#include <unistd.h>
#include <stdio.h>

char com_info[2] = {0, 0};

void on_signal1() {
    com_info[0]++;
    ft_printf("{%i}", com_info[0]);
}

void on_signal2()
{
   com_info[1] = 1;
   ft_printf("[%i]", com_info[1]);
}

void header()
{
    int pid;

    pid  = getpid();
    ft_printf("%i\n", pid);
}

int main()
{
    header();
    while (1)
    {
        if (com_info[2] == 1)
        {
            ft_printf("%i", com_info[0]);
            com_info[0] = 0;
            com_info[1] = 0;
        }
        signal(SIGUSR1, on_signal1);
        signal(SIGUSR2, on_signal2);
    }
}
