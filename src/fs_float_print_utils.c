/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_float_print_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:50:50 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/26 01:36:56 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int			print_right_f(int len, t_pf *prm)
{
	char	*res;
	int		ret;

	ret = 0;
	if (len < 19)
		res = ft_itoa_f(prm->rm, prm->prec);
	else
		res = print_f_rest(prm->dbl, prm->prec);
	ret = write(1, res, prm->prec);
	free(res);
	res = NULL;
	return (ret);
}

char		*left_part_f(long double d, int len)
{
	char		*res;
	size_t		n;
	int			i;
	long double	tmp;

	i = 1;
	res = (char *)ft_calloc(sizeof(char), len + 1);
	if (!res)
		ft_printf(NULL);
	while (i <= len)
	{
		tmp = d / ft_pow(10, len - i);
		n = (size_t)tmp;
		d -= (long double)n * ft_pow(10, len - i);
		res[i - 1] = (size_t)n % 10 + '0';
		i++;
	}
	return (res);
}

static void	correct_num_str(char **str, int i)
{
	if (*(*str + i) != '9')
		*(*str + i) = *(*str + i) - '0' + 1 + '0';
	else
	{
		*(*str + i) = '0';
		while (i--)
		{
			if (*(*str + i) != '9')
			{
				*(*str + i) = *(*str + i) - '0' + 1 + '0';
				break ;
			}
			else
				*(*str + i) = '0';
		}
	}
}

char		*print_f_rest(long double n, int len)
{
	char	*str;
	int		i;
	int		digit;

	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		ft_printf(NULL);
	i = 0;
	while (i < len)
	{
		n = n * 10.0;
		digit = (size_t)n % 10;
		str[i] = digit + '0';
		++i;
		n -= digit;
	}
	digit = (size_t)(n * 10.0) % 10;
	if (digit > 4)
	{
		if (digit > 5 || ((size_t)(n * 100000.0) > 50000) ||\
			((str[len - 1] - '0') && (((str[len - 1] - '0') % 10) % 2)))
			correct_num_str(&str, i - 1);
	}
	return (str);
}

char		*ft_itoa_f(size_t n, int len)
{
	char	*res;

	res = (char *)ft_calloc(sizeof(char), len + 1);
	if (!res)
		ft_printf(NULL);
	while (len)
	{
		res[len - 1] = (n % 10) + '0';
		--len;
		n = n / 10;
	}
	return (res);
}
