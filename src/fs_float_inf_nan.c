/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_float_inf_nan.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:26:08 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/21 22:35:12 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static uint32_t	dbl_exponent(uint64_t bits)
{
	return ((bits >> 52) & 0x7FF);
}

static uint64_t	dbl_mantissa(uint64_t bits)
{
	return (bits & 0xFFFFFFFFFFFFFull);
}

void			check_inf_nan(uint64_t bits, t_pf *prm)
{
	uint32_t	exponent;
	uint64_t	mantissa;

	exponent = dbl_exponent(bits);
	mantissa = dbl_mantissa(bits);
	if (exponent == 0x7FF)
	{
		if (mantissa == 0)
			prm->f |= inf;
		else
			prm->f |= nan;
	}
}

int				print_inf_nan(t_pf *prm)
{
	if (prm->f & inf)
		return (write(1, "inf", 3));
	else if (prm->f & nan)
		return (write(1, "nan", 3));
	return (0);
}
