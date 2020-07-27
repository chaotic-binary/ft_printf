/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_get_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:25:06 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/23 04:02:33 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	ft_atoi_fmt(const char **str, int *field)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = (**str == '-') ? -1 : 1;
	if (**str == '-' || **str == '+' || **str == ' ')
		++*str;
	while (**str >= '0' && **str <= '9')
	{
		nb = nb * 10 + sign * (**str - '0');
		++*str;
	}
	*field = nb;
	while (**str == '-' || **str == '+' || **str == ' ')
		++*str;
}

static void	get_w_aster(const char **str, t_pf *prm, va_list arg)
{
	int n;

	n = va_arg(arg, int);
	if (n < 0)
	{
		prm->width = (int)(-(long)n);
		prm->f |= minus;
	}
	else
		prm->width = n;
	++*str;
}

static void	process_flags(const char **str, t_pf *prm)
{
	while (**str && ft_strchr(FLAGS, **str))
	{
		if (**str == '0')
			prm->f |= zero;
		if (**str == '-')
			prm->f |= minus;
		if (**str == ' ')
			prm->sign |= space;
		if (**str == '+')
			prm->sign |= plus;
		if (**str == '#')
			prm->f |= hash;
		if (**str == 'l' && !(prm->f & ll))
			prm->f += l;
		if (**str == 'h' && !(prm->f & hh))
			prm->f += h;
		if (**str == 'L')
			prm->f |= L;
		++*str;
	}
}

static void	ft_pf_init(t_pf *prm)
{
	prm->width = 0;
	prm->prec = -1;
	prm->f = 0;
	prm->sign = 0;
	prm->prefix = 0;
	prm->len = 0;
	prm->num = 0;
	prm->rm = 0;
	prm->dbl = 0.0;
}

void		get_params(const char **str, t_pf *prm, va_list arg)
{
	if (!**str)
		return ;
	ft_pf_init(prm);
	process_flags(str, prm);
	if (**str == '*')
		get_w_aster(str, prm, arg);
	else
		ft_atoi_fmt(str, &(prm->width));
	process_flags(str, prm);
	if (**str == '.')
	{
		++*str;
		if (**str == '*')
		{
			prm->prec = va_arg(arg, int);
			++*str;
		}
		else
			ft_atoi_fmt(str, &(prm->prec));
	}
	process_flags(str, prm);
}
