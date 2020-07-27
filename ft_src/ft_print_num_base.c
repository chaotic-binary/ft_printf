/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:45:11 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/23 15:08:43 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	print_num_base(size_t n, size_t bs, int len)
{
	char		res[len];
	int			i;
	int			shift;
	static char	digits[] = "0123456789abcdef0123456789ABCDEF";

	if (len == 0)
		return (0);
	shift = (bs & capitals) ? 16 : 0;
	if (shift)
		bs = 16;
	i = len - 1;
	while (i >= 0)
	{
		res[i] = digits[n % bs + shift];
		i--;
		n = n / bs;
	}
	return (write(1, res, len));
}
