# include "ft_dprintf.h"
# include <stdio.h>
int	main(int ac, char **av)
{
	if (ac > 1)
	{
		dprintf(1, " %d\n", ft_dprintf(1, "%#0hhd", ft_atoi(av[ac - 1]), ft_atoi(av[ac -1]), 1244208544561054792));
		   dprintf(1, " %d\n", dprintf(1, "%#0hhd", ft_atoi(av[ac - 1]), ft_atoi(av[ac -1]), 1244208544561054792));
	}
}
