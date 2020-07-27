/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 00:35:04 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/23 14:15:58 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	print_pad(int const *const pad, char sym, t_pf *prm, int *ret)
{
	char	*str;

	if (*pad <= 0)
		return ;
	str = (char *)malloc(sizeof(char) * *pad);
	if (!str)
		ft_printf(NULL);
	ft_memset(str, sym, *pad);
	if (prm->sign && sym == '0')
	{
		*ret += write(1, &PREFIX[prm->sign], 1);
		prm->sign = 0;
	}
	if (prm->prefix && sym == '0')
	{
		*ret += write(1, &PREFIX[prm->prefix], 2);
		prm->prefix = 0;
	}
	*ret += write(1, str, *pad);
	free(str);
	str = NULL;
}

static void	print_arg(char c, t_pf *prm, va_list arg, int *ret)
{
	if (c == 'u' || c == 'd' || c == 'i')
		*ret += print_num_base(prm->num, 10, prm->len);
	else if (c == 'x' || c == 'p')
		*ret += print_num_base(prm->num, 16, prm->len);
	else if (c == 'X')
		*ret += print_num_base(prm->num, (16 + capitals), prm->len);
	else if (c == 'o')
		*ret += print_num_base(prm->num, 8, prm->len);
	else if (c == 's' && (prm->f & l))
		*ret += print_ws(va_arg(arg, wchar_t *), prm->len);
	else if (c == 's')
		*ret += print_s(va_arg(arg, char *), prm->len);
	else if (c == 'c' && (prm->f & l))
		*ret += ft_putwchar(va_arg(arg, wint_t));
	else if (c == 'c')
		*ret += ft_putchar_intret(va_arg(arg, int));
	else if (c == '%')
		*ret += write(1, "%", 1);
	else if (c == 'f')
		*ret += print_float(prm);
	else if (c == 'e')
		*ret += print_e((long double)va_arg(arg, double), prm);
	else if (c == 'g')
		*ret += print_g((long double)va_arg(arg, double), prm);
}

static void	print_fmt(char c, t_pf *prm, va_list arg, int *ret)
{
	va_list	argcpy;
	char	sym;

	va_copy(argcpy, arg);
	sym = calc_params(c, prm, arg);
	if (!(prm->f & minus))
		print_pad(&prm->width, sym, prm, ret);
	if (c != 'f' && c != 'e' && c != 'g')
		print_pad(&prm->prec, '0', prm, ret);
	if (prm->sign)
		*ret += write(1, &PREFIX[prm->sign], 1);
	if (prm->prefix)
		*ret += write(1, &PREFIX[prm->prefix], 2);
	if (c == 'c' && (prm->f & l) == 0)
		print_arg(c, prm, arg, ret);
	else
		print_arg(c, prm, argcpy, ret);
	if (prm->f & minus)
		print_pad(&prm->width, ' ', prm, ret);
	va_end(argcpy);
}

static void	process_fmt(const char **s, t_pf *prm, va_list arg, int *ret)
{
	int *n;

	++*s;
	get_params(s, prm, arg);
	if (!**s)
		return ;
	else if (ft_strchr(SPC, **s))
	{
		if (**s == 'n')
		{
			if ((n = va_arg(arg, int *)))
				*n = *ret;
		}
		else
			print_fmt(**s, prm, arg, ret);
	}
	else
		*ret += write(1, &**s, 1);
	++*s;
}

int			ft_printf(const char *s, ...)
{
	t_pf	prm;
	va_list	arg;
	int		ret;
	char	*fin;

	va_start(arg, s);
	ret = 0;
	if (s == NULL)
		return (-1);
	while (*s)
	{
		if (*s != '%')
		{
			fin = ft_strchr(s, '%');
			if (!fin)
				fin = ft_strchr(s, '\0');
			ret += write(1, s, fin - s);
			s = fin;
		}
		if (*s == '%')
			process_fmt(&s, &prm, arg, &ret);
	}
	va_end(arg);
	return (ret);
}
