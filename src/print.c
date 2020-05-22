#include "ft_dprintf.h"

void	loop_char(t_data *d, char c, size_t loop)
{
	while (loop > 0)
	{
		write(d->fd, &c, 1);
		d->ret++;
		loop--;
		d->wid_pre.width--;
		//ft_putchar(';');
		//ft_putnbr(loop);
	}
}

void	_string(t_data *d, char *str)
{
	size_t	l;
	size_t	i;

	!str && (d->wid_pre.precision >= 6 || !(d->flag & _dot)) ? str = "(null)": 0;
	!str ? str = "" : 0;
	l = ft_strlen(str);
	l = l > d->wid_pre.precision && (d->flag & _dot) ? d->wid_pre.precision : l;
	i = 0;
	!(d->flag & _left) && l < d->wid_pre.width ? loop_char(d, ' ', d->wid_pre.width - l) : 0;
	while (i < l && ++d->ret)
		write(d->fd, &str[i++], 1);
	(d->flag & _left) && l < d->wid_pre.width ? loop_char(d, ' ', d->wid_pre.width - l) : 0;
}

void	_char(t_data *d, int c)
{
	!(d->flag & _left) ? loop_char(d, ' ', d->wid_pre.width - 1) : 0;
	write(d->fd, &c, 1);
	d->ret++;
	(d->flag & _left) ? loop_char(d, ' ', d->wid_pre.width - 1) : 0;
}

void	reset_data(t_data *d)
{
	ft_bzero(&d->wid_pre, sizeof(t_width_precision));
	d->flag = 0;
	d->specif = 0;
	d->length = 0;
}

void	_put_str(t_data *d, char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		write(d->fd, &str[i++], 1);
		d->ret++;
		d->wid_pre.width--;
	}
}

void	_put_decimal(t_data *d, char *str)
{
	size_t	l;
	size_t	new_l;
	char	*ptr;

	ptr = str;
	l = ft_strlen(str);
	str[0] == '-' ? d->wid_pre.precision++ : 0;
	new_l = l > d->wid_pre.precision ? l : d->wid_pre.precision;
	(d->flag & _space) && !(d->flag & _plus) ? loop_char(d, ' ', 1) : 0;
	(d->flag & _plus) && str[0] != '-' ? d->wid_pre.width-- : 0;
	!(d->flag & _left) && d->wid_pre.width > 0 && d->wid_pre.width > new_l ? loop_char(d, ' ', d->wid_pre.width - new_l) : 0;
	d->flag & _plus && str[0] != '-' ? loop_char(d, '+', 1) : 0;
	(d->flag & _zero) && str[0] == '-' ? new_l-- : 0;
	l = (d->flag & _zero) && (d->flag & _plus) && str[0] != '-'  ? l + 1 : l;
	str[0] == '-' && str++ ? loop_char(d, '-', 1) : 0;
	l < new_l ? loop_char(d, '0', new_l - l) : 0;
	new_l < d->wid_pre.width && d->wid_pre.width > 0 && !(d->flag & _left) ? loop_char(d, '.', d->wid_pre.width - new_l) : 0;
	_put_str(d, str);
	(d->flag & _left) && d->wid_pre.width > 0 ? loop_char(d, ' ', d->wid_pre.width) : 0;
	free(ptr);
}

void	_decimal(t_data *d)
{
	!(d->length)? _put_decimal(d, ft_itoa(va_arg(d->ap, int))) : 0;
	(d->length & _l) ? _put_decimal(d, ft_ltoa(va_arg(d->ap, long int))) : 0;
	(d->length & _ll) ? _put_decimal(d, ft_lltoa(va_arg(d->ap, long long int))) : 0;
	(d->length & _h) ? _put_decimal(d, ft_itoa((short int)(va_arg(d->ap, int)))) : 0;
	(d->length & _hh) ? _put_decimal(d, ft_itoa((char)(va_arg(d->ap, int)))) : 0;
}

void	get_arg(t_data *d)
{
	(d->specif & _MOD) ? loop_char(d, '%', 1) : 0;
	(d->specif & _s) ? _string(d, va_arg(d->ap, char *)) : 0;
	(d->specif & _c) ? _char(d, va_arg(d->ap, int)) : 0;
	(d->specif & _di) ? _decimal(d) : 0;
	reset_data(d);
}


