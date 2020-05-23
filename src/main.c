#include "ft_dprintf.h"
#include <stdio.h>


int	main(int ac, char **av)
{
	if (ac > 1)
	{
		printf("|  %d\n", ft_dprintf(0,"%7p", NULL));
		printf("|  %d\n",	printf("%7p", NULL));
	}
}
