#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r')
		|| nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nbr = nbr * 10 + (nptr[i++] - '0');
	return (nbr);
}

int main(int argc, char **argv)
{
    int pid;
    int i;

    if (argc < 2)
        return(ft_printf("Error"));
    pid = ft_atoi(argv[1]);
    i = 65;
    while (i-- > 0)
        kill(pid, SIGUSR1);
    kill(pid, SIGUSR2);
    ft_printf("Done");
}