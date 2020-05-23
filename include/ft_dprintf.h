#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

#include "libft.h"
#include <stdarg.h>

# define _c	1
# define _s	2
# define _p	4
# define _di	8
# define _o	16
# define _u	32
# define _x	64
# define _X	128
# define _MOD	256
# define _b	512

# define _h	1
# define _hh	2
# define _l	4
# define _ll	8

# define _left	1
# define _hash	2
# define _plus	4
# define _zero	8
# define _space	16
# define _dot	32


typedef struct			s_width_precision
{
	int			width;
	int			precision;
}				t_width_precision;

typedef struct			s_data
{
	va_list			ap;
	int			fd;
	const char		*str;
	size_t			i;
	int			ret;
	int			flag;
	short			specif;
	short			length;
	t_width_precision	wid_pre;
}				t_data;


int	ft_printf(const char *format, ...);
int	ft_dprintf(int fd, const char *format, ...);
void	get_arg(t_data *d);
#endif
