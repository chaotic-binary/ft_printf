/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_g.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:31:15 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/25 22:42:52 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	run_f(long double n, int *len, int const *const p, t_pf *prm)
{
	size_t	x;

	x = prm->rm;
	prm->prec = *p - 1 - *len;
	if (prm->prec < 0)
		prm->prec = 0;
	*len = count_len_f(prm, &n);
	if (n < 1.0 && prm->rm == ++x && prm->rm % 10 == 0)
	{
		--prm->prec;
		prm->rm /= 10;
	}
}

int			calc_g(t_pf *prm, va_list arg)
{
	long double	n;
	int			p;
	int			len;

	n = get_arg_f(prm, arg);
	if (prm->prec == 0)
		prm->prec = 1;
	p = prm->prec;
	--prm->prec;
	len = count_len_e(n, prm);
	prm->f |= g;
	len = (n < 1.0) ? -prm->len : prm->len;
	if (len >= -4 && len < p)
		run_f(n, &len, &p, prm);
	else
	{
		prm->f |= e;
		prm->prec = p - 1;
		prm->len = 0;
		len = count_len_e(n, prm);
	}
	return (len);
}

int			print_g(long double n, t_pf *prm)
{
	int ret;

	if (prm->f & e)
		ret = print_e(n, prm);
	else
		ret = print_float(prm);
	return (ret);
}
