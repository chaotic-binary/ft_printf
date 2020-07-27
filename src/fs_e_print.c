/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_e_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:50:50 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/25 23:51:57 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	print_exp(int small, int *ret, t_pf *prm)
{
	if (small && prm->len != 0)
		*ret += write(1, "e-", 2);
	else
		*ret += write(1, "e+", 2);
	if (prm->len > 99)
		*ret += print_num_base(prm->len, 10, 3);
	else
		*ret += print_num_base(prm->len, 10, 2);
}

static int	left_part_e(int small, int *nlen, char **res, t_pf *prm)
{
	int ret;

	ret = 0;
	if (prm->len > 18 && prm->prec > 17 && !small)
	{
		*nlen = countdigits_double(prm->dbl);
		*res = left_part_f(prm->dbl, *nlen);
	}
	else
	{
		*nlen = countdigits_base(prm->num, 10);
		*res = ft_itoa_f(prm->num, *nlen);
	}
	ret += write(1, *res, 1);
	if (prm->prec || (prm->f & hash))
		ret += write(1, ".", 1);
	return (ret);
}

int			print_e(long double n, t_pf *prm)
{
	int		ret;
	int		len;
	int		nlen;
	int		small;
	char	*res;

	if (prm->f & nan || prm->f & inf)
		return (print_inf_nan(prm));
	ret = 0;
	small = (n < 1.0 && n > -1.0);
	ret += left_part_e(small, &nlen, &res, prm);
	if (prm->prec)
	{
		if (nlen - 1)
		{
			len = ft_min(nlen - 1, prm->prec);
			ret += write(1, &res[1], len);
			prm->prec = (prm->prec <= len) ? 0 : prm->prec - len;
		}
		ret += print_right_f(small ? prm->prec + prm->len : prm->prec, prm);
	}
	print_exp(small, &ret, prm);
	free(res);
	res = NULL;
	return (ret);
}
