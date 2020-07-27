/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_calc_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:21:52 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/23 05:48:00 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	calc_arg_len(char c, t_pf *prm, va_list arg)
{
	int len;

	len = 0;
	if (c == 'u' || c == 'x' || c == 'X' || c == 'p' || c == 'o')
		len = count_len_uns(c, prm, arg);
	else if (c == 'd' || c == 'i')
		len = count_len_sn(prm, arg);
	else if (c == 's' && (prm->f & l))
		len = ft_wstrlen_pf(va_arg(arg, wchar_t *));
	else if (c == 's')
		len = ft_strlen_pf(va_arg(arg, char *));
	else if (c == 'c' && (prm->f & l))
		len = ft_wcharlen(va_arg(arg, int));
	else if (c == 'c' || c == '%')
		len = 1;
	else if (c == 'f')
		len = calc_f(prm, arg);
	else if (c == 'e')
		len = calc_e(prm, arg);
	else if (c == 'g')
		len = calc_g(prm, arg);
	return (len);
}

static void	calc_basic_rule(int const *const alen, t_pf *prm)
{
	int	tmp;

	if (prm->prec < 0)
		prm->prec = 0;
	if (prm->prefix || prm->sign)
		tmp = prm->prec - prm->len;
	else
		tmp = prm->prec - *alen;
	prm->prec = (tmp > 0) ? tmp : 0;
	prm->width = prm->width - prm->prec - *alen;
}

static void	calc_lenparams_f(int *alen, t_pf *prm)
{
	if (prm->f & nan || prm->f & inf)
	{
		if (prm->f & nan)
			prm->sign = 0;
		prm->prec = 0;
		if (prm->f & zero)
			prm->f -= zero;
	}
	else
	{
		if (prm->prec || (prm->f & hash))
			++*alen;
	}
	if (prm->sign)
		++*alen;
	prm->width = prm->width - prm->prec - *alen;
}

char		calc_params(char c, t_pf *prm, va_list arg)
{
	int		alen;
	char	sym;

	alen = calc_arg_len(c, prm, arg);
	if (c == 's')
	{
		prm->len = (prm->prec < 0) ? alen : ft_min(prm->prec, alen);
		prm->prec = 0;
		prm->width = prm->width - prm->len;
		prm->sign = 0;
	}
	else if (c == 'f' || c == 'e' || c == 'g')
		calc_lenparams_f(&alen, prm);
	else
	{
		if (c != 'c' && c != '%' && (prm->f & zero) && prm->prec > -1)
			prm->f -= zero;
		if (c == 'c' || c == '%')
			prm->prec = 0;
		calc_basic_rule(&alen, prm);
	}
	sym = (prm->f & zero) ? '0' : ' ';
	return (sym);
}
