/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_e_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:50:50 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/26 02:47:26 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	get_parts(long double *n, long double *d, int l, t_pf *prm)
{
	if (l > 20)
	{
		g_set_prec(l - 1, prm);
		g_correct_prec_l(prm, &l);
	}
	if (l < 20)
	{
		if (int_part_len(d, prm->prec - l + 1, prm) > l)
		{
			if (*n < 1.0)
				--prm->len;
			else
				++prm->len;
		}
		if (prm->prec == l - 1)
			g_trim_zeroes(&prm->num, &prm->prec, prm);
	}
}

static void	cut_left_f(long double *n, long double *d, int len, t_pf *prm)
{
	int		l;
	size_t	rm;

	if (prm->prec < 19)
	{
		*d = *d / ft_pow(10, len - prm->prec - 1);
		l = countdigits_double(*d);
		rm = (size_t)*d;
		if (*d - rm > 0.5 || (((rm % 10) % 2) && rm))
			*d += 0.5;
		prm->num = (size_t)*d;
		prm->dbl = *d;
		if (countdigits_base(prm->num, 10) > l)
			++prm->len;
		g_trim_zeroes(&prm->num, &prm->prec, prm);
	}
	else
	{
		l = prm->prec + 1;
		prm->dbl = *d / ft_pow(10, len - l);
		g_correct_prec_l(prm, &l);
		if (prm->prec >= l - 1)
			get_parts(n, &prm->dbl, l, prm);
	}
}

int			count_len_e(long double n, t_pf *prm)
{
	int			l;
	long double	d;

	if (prm->f & nan || prm->f & inf)
		return (3);
	d = n;
	l = countdigits_double(d);
	if (d < 1.0 && d != 0)
	{
		while (d < 1.0)
		{
			d *= 10;
			++prm->len;
		}
		prm->dbl = d;
	}
	prm->len = l - 1 + prm->len;
	if (prm->prec < l - 1)
		cut_left_f(&n, &d, l, prm);
	else
		get_parts(&n, &d, l, prm);
	return (5);
}

int			calc_e(t_pf *prm, va_list arg)
{
	long double	n;
	int			len;

	n = get_arg_f(prm, arg);
	len = count_len_e(n, prm);
	return (len);
}
