/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_diuxp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 10:37:46 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/23 21:55:48 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static size_t		get_arg_usn(char c, t_pf *prm, va_list arg)
{
	size_t n;

	if (c == 'p')
		n = va_arg(arg, size_t);
	else if (prm->f & ll)
		n = (size_t)va_arg(arg, unsigned long long);
	else if (prm->f & l)
		n = (size_t)va_arg(arg, unsigned long);
	else if (prm->f & hh)
		n = (size_t)((unsigned char)va_arg(arg, unsigned int));
	else if (prm->f & h)
		n = (size_t)((unsigned short)va_arg(arg, unsigned int));
	else
		n = (size_t)va_arg(arg, unsigned int);
	return (n);
}

int					count_len_uns(char c, t_pf *prm, va_list arg)
{
	int		len;
	size_t	n;

	n = get_arg_usn(c, prm, arg);
	if (prm->prec == 0 && n == 0 && !(c == 'o' && (prm->f & hash)))
		len = 0;
	else if (c == 'u')
		len = countdigits_base(n, 10);
	else if (c == 'o')
		len = countdigits_base(n, 8);
	else
		len = countdigits_base(n, 16);
	prm->len = len;
	prm->num = n;
	if (c == 'o' && (prm->f & hash) && n > 0)
	{
		++len;
		++prm->len;
	}
	else if (c == 'p' || (c != 'u' && (prm->f & hash) && n > 0))
	{
		len += 2;
		prm->prefix = (c == 'X') ? 6 : 4;
	}
	return (len);
}

static long long	get_arg_sn(t_pf *prm, va_list arg)
{
	long long	n;

	if (prm->f & ll)
		n = va_arg(arg, long long);
	else if (prm->f & l)
		n = (long long)va_arg(arg, long);
	else if (prm->f & hh)
		n = (long long)((signed char)va_arg(arg, int));
	else if (prm->f & hh)
		n = (long long)((short int)va_arg(arg, int));
	else
		n = (long long)va_arg(arg, int);
	return (n);
}

int					count_len_sn(t_pf *prm, va_list arg)
{
	int			len;
	long long	n;

	n = get_arg_sn(prm, arg);
	if (n < 0)
	{
		prm->sign = minus;
		n = -n;
	}
	if (prm->prec == 0 && n == 0)
		len = 0;
	else
		len = countdigits_base(n, 10);
	prm->len = len;
	prm->num = (size_t)n;
	if (prm->sign)
		++len;
	return (len);
}
