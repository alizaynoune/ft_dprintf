#include "ft_dprintf.h"

#include <stdio.h>

//int		ft_printf(char const *, ...);

int		main(void)
{
	unsigned long	lb;

	ft_printf("ft_printf ret = %d\n", ft_printf("%%p::[%p]\n", &lb));
	printf("printf ret = %d\n", printf("%%p::[%p]\n", &lb));
	return (0);
}
