#include "ft_dprintf.h"
#include <stdio.h>

int	ft_printf(const char *format, ...)
{
	return(ft_dprintf(0, format));
}


int	main(int ac, char **av)
{
	if (ac > 1)
	{
		printf("|  %d\n", ft_dprintf(0, av[1], ft_atoi(av[2])));
		printf("|  %d\n",	dprintf(0,av[1], ft_atoi(av[2])));
	}
}
