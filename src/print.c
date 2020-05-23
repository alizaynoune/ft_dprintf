#include "ft_dprintf.h"

void	loop_char(t_data *d, char c, int loop)
{
	while (loop > 0)
	{
		write(d->fd, &c, 1);
		d->ret++;
		loop--;
		d->wid_pre.width--;
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
	!(d->flag & _left) > 0 ? loop_char(d, ' ', d->wid_pre.width - 1) : 0;
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

void	_put_hash(t_data *d)
{
	write(d->fd, "0", 1);
	(d->specif & _x) || (d->specif & _p) ? write(d->fd, "x", 1) : 0;
	d->specif & _X ? write(d->fd, "X", 1) : 0;
	if (d->specif & _x || d->specif & _X || d->specif & _p)
	{
		d->ret += 2;
		d->wid_pre.width -+ 2;
	}
	else
	{
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
	if ((d->flag & _hash))
	{
		d->wid_pre.width -= (d->specif & _o) ? 1 : 2;
		l += (d->specif & _o) ? 1 : 2;
	}
	new_l = l > d->wid_pre.precision ? l : d->wid_pre.precision;
	(d->flag & _space) && str[0] != '-' ? loop_char(d, ' ', 1) : 0;
	(d->flag & _plus) && str[0] != '-' ? d->wid_pre.width-- : 0;
	!(d->flag & _left) && d->wid_pre.width > 0 && d->wid_pre.width > new_l ? loop_char(d, ' ', d->wid_pre.width - new_l) : 0;
	d->flag & _plus && str[0] != '-' ? loop_char(d, '+', 1) : 0;
	(d->flag & _hash) || (d->specif & _p) ? _put_hash(d): 0;
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

char	*_unsigned_str(unsigned long long int value)
{
	char		*str;
	int		i;
	unsigned long long int	nbr;

	i = !value ? 1 : 0;
	nbr = value;
	while ((nbr /= 10))
		i++;
	if (!(str = (char *)ft_memalloc(i + 1)))
		exit(1); //free;
	while (i >= 0)
	{
		str[i--] = (value % 10) + '0';
		value /= 10;
	}
	return(str);
}

void	_unsigned(t_data *d)
{
	!(d->length)? _put_decimal(d, (_unsigned_str(va_arg(d->ap, unsigned int)))): 0;
	(d->length & _l) ? _put_decimal(d, (_unsigned_str(va_arg(d->ap, unsigned long int)))) : 0;
	(d->length & _ll) ? _put_decimal(d, (_unsigned_str(va_arg(d->ap, unsigned long long int)))) : 0;
	(d->length & _h) ? _put_decimal(d, (_unsigned_str((unsigned short int)(va_arg(d->ap, unsigned int))))) : 0;
	(d->length & _hh) ? _put_decimal(d, (_unsigned_str((unsigned char)(va_arg(d->ap, unsigned int))))) : 0;
}

char	*_unsigned_base_str(unsigned long long int value, char *s_, unsigned int base)
{
	unsigned long long int	nbr;
	char			*str;
	int			i;

	i = !value ? 1 : 0;
	nbr = value;
	while ((nbr /= base))
		i++;
	if (!(str = (char *)ft_memalloc(i + 1)))
		exit(1); //free;
	while (i >= 0)
	{
		str[i] = s_[value % base];
		value /= base;
		i--;
	}
	return (str);
}

void	_hexa(t_data *d)
{
	char	*x_;
	char	*X_;

	x_ = "0123456789abcdef";
	X_ = "0123456789ABCDEF";
	d->specif & _p ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned long long int), x_, 16)) : 0;
	if (d->specif & _x)
	{
		!(d->length) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned int), x_, 16)) : 0;
		(d->length & _l) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned long int), x_, 16)) : 0;
		(d->length & _ll) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned long long int), x_, 16)) : 0;
		(d->length & _h) ? _put_decimal(d, _unsigned_base_str((unsigned short int)(va_arg(d->ap, unsigned int)), x_, 16)) : 0;
		(d->length & _hh) ? _put_decimal(d, _unsigned_base_str((unsigned char)(va_arg(d->ap, unsigned int)), x_, 16)) : 0;
	}
	else if (d->specif & _X)
	{
		!(d->length) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned int), X_, 16)) : 0;
		(d->length & _l) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned long int), X_, 16)) : 0;
		(d->length & _ll) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned long long int), X_, 16)) : 0;
		(d->length & _h) ? _put_decimal(d, _unsigned_base_str((unsigned short int)(va_arg(d->ap, unsigned int)), X_, 16)) : 0;
		(d->length & _hh) ? _put_decimal(d, _unsigned_base_str((unsigned char)(va_arg(d->ap, unsigned int)), X_, 16)) : 0;
	}
}

void	_octal(t_data *d)
{
	char	*s_;

	s_ = "01234567";
	!(d->length) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned int), s_, 8)) : 0;
	(d->length & _l) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned long int), s_, 8)) : 0;
	(d->length & _ll) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned long long int), s_, 8)) : 0;
	(d->length & _h) ? _put_decimal(d, _unsigned_base_str((unsigned short int)(va_arg(d->ap, unsigned int)), s_, 8)) : 0;
	(d->length & _hh) ? _put_decimal(d, _unsigned_base_str((unsigned char)(va_arg(d->ap, unsigned int)), s_, 8)) : 0;
}

void	_binary(t_data *d)
{
	char	*s_;

	s_ = "01";
	!(d->length) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned int), s_, 2)) : 0;
	(d->length & _l) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned long int), s_, 2)) : 0;
	(d->length & _ll) ? _put_decimal(d, _unsigned_base_str(va_arg(d->ap, unsigned long long int), s_, 2)) : 0;
	(d->length & _h) ? _put_decimal(d, _unsigned_base_str((unsigned short int)(va_arg(d->ap, unsigned int)), s_, 2)) : 0;
	(d->length & _hh) ? _put_decimal(d, _unsigned_base_str((unsigned char)(va_arg(d->ap, unsigned int)), s_, 2)) : 0;
}

void	get_arg(t_data *d)
{
	(d->specif & _MOD) ? loop_char(d, '%', 1) : 0;
	(d->specif & _s) ? _string(d, va_arg(d->ap, char *)) : 0;
	(d->specif & _c) ? _char(d, va_arg(d->ap, int)) : 0;
	(d->specif & _di) ? _decimal(d) : 0;
	(d->specif & _u) ? _unsigned(d) : 0;
	(d->specif & _x) || (d->specif & _X) || (d->specif & _p) ? _hexa(d) : 0;
	(d->specif & _o) ? _octal(d) : 0;
	(d->specif & _b) ? _binary(d): 0;
	reset_data(d);
}


