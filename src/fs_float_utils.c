/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_float_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:50:50 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/25 23:52:17 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static long double	get_arg_ld(t_pf *prm, va_list arg)
{
	long double			res;
	union u_dbl_union	u_dbl;

	if (prm->f & L)
	{
		res = va_arg(arg, long double);
		u_dbl.n_dbl = res;
		if (res < 0 || ((res == 0) && ((u_dbl.n_bits >> 63) != 0)))
		{
			prm->sign = minus;
			res = -res;
		}
	}
	else
	{
		u_dbl.n_dbl = va_arg(arg, double);
		res = (long double)u_dbl.n_dbl;
		if (((u_dbl.n_bits >> 63) != 0))
		{
			prm->sign = minus;
			res = -res;
		}
		check_inf_nan(u_dbl.n_bits, prm);
	}
	return (res);
}

long double			get_arg_f(t_pf *prm, va_list arg)
{
	long double n;

	prm->prec = (prm->prec < 0) ? 6 : prm->prec;
	n = get_arg_ld(prm, arg);
	prm->dbl = n;
	return (n);
}

int					int_part_len(long double *n, int len, t_pf *prm)
{
	long double tmp;

	prm->num = (size_t)(*n);
	tmp = *n - prm->num;
	prm->dbl = tmp;
	if (len > 19)
		g_correct_prec(prm, &len);
	tmp = tmp * ft_pow(10, len);
	prm->rm = (len == 0) ? prm->num : (size_t)tmp;
	if ((tmp > 0.5 && len == 0) || (tmp - prm->rm > 0.5 && len > 0) ||\
		(((prm->rm % 10) % 2) && prm->rm))
		tmp += 0.5;
	prm->rm = (size_t)tmp;
	if (prm->num ^ SIZE_MAX)
		prm->num += tmp / ft_pow(10, len);
	if (len < 20)
	{
		g_trim_zeroes(&prm->rm, &prm->prec, prm);
		g_set_prec(prm->prec - len, prm);
	}
	len = countdigits_base(prm->num, 10);
	return (len);
}

int					countdigits_double(long double n)
{
	int count;

	count = 1;
	while (n / 10.0 >= 1.0)
	{
		count++;
		n /= 10.0;
	}
	return (count);
}

long double			ft_pow(long double n, size_t pow)
{
	long double res;

	res = 1;
	while (pow--)
		res *= n;
	return (res);
}
