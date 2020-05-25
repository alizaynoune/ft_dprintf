#include "ft_dprintf.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	int	ft = 0;
	int	sys = 0;
	int	fd;
	char	*str;
	long long int value;
	fd = 0;
	if (ac == 4 && av[1][0] == 'd')
	{
		str = av[2];
		value = ft_atoll(av[3]);
		dprintf(fd, "| %d",ft_dprintf(fd,str, value));
		dprintf(fd, "\n");
		dprintf(fd, "| %d",dprintf(fd, str, value));
		dprintf(fd, "\n");
	}
	if (ac == 4 && av[1][0] == 's')
	{
		str = av[2];
		dprintf(fd, "| %d",ft_dprintf(fd,str, av[3]));
		dprintf(fd, "\n");
		dprintf(fd, "| %d",dprintf(fd, str, av[3]));
		dprintf(fd, "\n");
	}
}
