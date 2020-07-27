/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_f.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:50:50 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/25 23:48:50 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	print_dbl_max(void)
{
	char *str;

	str = "17976931348623157081452742373170435679807056752";
	write(1, str, 47);
	str = "584499659891747680315726078002853876058955863276687817";
	write(1, str, 54);
	str = "154045895351438246423432132688946418276846754670353751";
	write(1, str, 54);
	str = "698604991057655128207624549009038932894407586850845513";
	write(1, str, 54);
	str = "394230458323690322294816580855933212334827479782620414";
	write(1, str, 54);
	str = "4723168738177180919299881250404026184124858368";
	write(1, str, 46);
	return (309);
}

static int	print_left_f(t_pf *prm)
{
	char *res;

	if (prm->len > 19)
		res = left_part_f(prm->dbl, prm->len);
	else
		res = ft_itoa_f(prm->num, prm->len);
	write(1, res, prm->len);
	free(res);
	res = NULL;
	return (prm->len);
}

int			print_float(t_pf *prm)
{
	int ret;

	if (prm->f & nan || prm->f & inf)
		return (print_inf_nan(prm));
	ret = 0;
	if (prm->dbl == DBL_MAX)
		ret += print_dbl_max();
	else
		ret += print_left_f(prm);
	if (prm->prec || (prm->f & hash))
		ret += write(1, ".", 1);
	if (prm->prec)
		ret += print_right_f(prm->prec, prm);
	return (ret);
}

int			count_len_f(t_pf *prm, long double *n)
{
	int len;

	if (prm->f & nan || prm->f & inf)
		return (3);
	len = countdigits_double(*n);
	if (len < 20)
		len = int_part_len(n, prm->prec, prm);
	prm->len = len;
	if (len > 20)
		g_set_prec(0, prm);
	return (len);
}

int			calc_f(t_pf *prm, va_list arg)
{
	int			len;
	long double	n;

	n = get_arg_f(prm, arg);
	len = count_len_f(prm, &n);
	return (len);
}
