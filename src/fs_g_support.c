/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_g_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:31:15 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/25 23:06:42 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	g_correct_prec(t_pf *prm, int *len)
{
	int		i;
	char	*right;

	if ((prm->f & g) && !(prm->f & hash))
	{
		i = prm->prec;
		right = print_f_rest(prm->dbl, prm->prec);
		while (--i && *(right + i) == '0' && *len)
		{
			--prm->prec;
			--*len;
		}
		free(right);
		right = NULL;
	}
}

void	g_correct_prec_l(t_pf *prm, int *len)
{
	int		i;
	char	*left;

	if ((prm->f & g) && !(prm->f & hash))
	{
		i = *len;
		left = left_part_f(prm->dbl, *len);
		while (--i && *(left + i) == '0')
		{
			while (prm->prec)
				--prm->prec;
			prm->dbl /= 10.0;
			--*len;
		}
		free(left);
		left = NULL;
	}
}

void	g_trim_zeroes(size_t *n, int *len, t_pf *prm)
{
	if ((prm->f & g) && !(prm->f & hash))
	{
		if (*n == 0 || *len == 0)
			return ;
		else
		{
			while (*n % 10 == 0 && *len)
			{
				*n /= 10;
				--*len;
			}
		}
	}
}

void	g_set_prec(int x, t_pf *prm)
{
	if ((prm->f & g) && !(prm->f & hash))
	{
		if (prm->rm == 0)
			prm->prec = x;
	}
}
