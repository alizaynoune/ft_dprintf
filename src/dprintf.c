#include "ft_dprintf.h"

void	_putformat(t_data *d)
{
	ft_putchar_fd(d->str[d->i++], d->fd);
	d->ret++;
}

void	_length(t_data *d)
{
	if (d->str[d->i] == 'l' || d->str[d->i] == 'h')
	{
		if (d->str[d->i] == 'l')
			d->str[d->i + 1] == 'l' ? d->length |= _ll : (d->length |= _l);
		else if (d->str[d->i] == 'h')
			d->str[d->i + 1] == 'h' ? d->length |= _hh : (d->length |= _h);
		(d->length & _ll) || (d->length & _hh) ? d->i += 2 : d->i++;
	}
}

void	width_precision(t_data *d)
{
	d->wid_pre.width = ft_atoi(&d->str[d->i]);
	while (ft_isdigit(d->str[d->i]))
		d->i++;
	if (d->str[d->i] == '.')
	{
		d->flag |= _dot;
		d->i++;
		d->flag -= (d->flag & _zero);
	}
	d->wid_pre.precision = ft_atoi(&d->str[d->i]);
	while (ft_isdigit(d->str[d->i]))
		d->i++;
	d->flag & _zero && d->flag & _left ? d->flag -= (d->flag & _zero) : 0;
	if (d->flag & _zero)
	{
		d->wid_pre.precision = d->wid_pre.width;
		d->wid_pre.width = 0;
	}
}

void	_flags(t_data *d)
{
	while (d->str[d->i])
	{
		if (d->str[d->i] == '#')
			d->flag |= _hash;
		else if (d->str[d->i] == ' ')
			d->flag |= _space;
		else if (d->str[d->i] == '0')
			d->flag |= _zero;
		else if (d->str[d->i] == '-')
			d->flag = _left;
		else if (d->str[d->i] == '+')
			d->flag = _plus;
		else
			break ;
		d->i++;
	}
}

void	_specifier(t_data *d)
{
	d->str[d->i] == 's' ? d->specif |= _s : 0;
	d->str[d->i] == 'c' ? d->specif |= _c : 0;
	d->str[d->i] == 'p' ? d->specif |= _p : 0;
	d->str[d->i] == 'i' || d->str[d->i] == 'd' ? d->specif |= _di : 0;
	d->str[d->i] == 'o' ? d->specif |= _o : 0;
	d->str[d->i] == 'u' ? d->specif |= _u : 0;
	d->str[d->i] == 'x' ? d->specif |= _x : 0;
	d->str[d->i] == 'X' ? d->specif |= _X : 0;
	d->str[d->i] == '%' ? d->specif |= _MOD : 0;
	d->specif ? d->i++ : 0;
}

void	_unkown(t_data *d)
{
	write(d->fd, "%", 1);
	(d->flag & _space) ? write(d->fd, " ", 1) : 0;
	(d->flag & _space) ? d->ret += 2: d->ret++;
}

void	read_format(t_data *d)
{
	size_t	cp;
	
	cp = ++d->i;
	if (d->str[d->i])
	{
		_flags(d);
		width_precision(d);
		_length(d);
		d->length ? cp = d->i : 0;
		_specifier(d);
		!d->specif && (d->i = cp) ? _unkown(d): get_arg(d);
	}
	else
		d->ret = -1;
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_data		d;

	d = *(t_data *)ft_memalloc(sizeof(t_data));
	ft_bzero(&d.wid_pre, sizeof(t_width_precision));
	d.str = format;
	va_start(d.ap, format);
	while (d.str[d.i] && d.ret != -1)
		d.str[d.i] == '%' ? read_format(&d): _putformat(&d);
	va_end(d.ap);
	return (d.ret);
}
