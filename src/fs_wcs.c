/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_wcs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:16:10 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/20 18:52:54 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	ft_putwchar(wint_t c)
{
	unsigned int	len;
	char			s[4];

	len = ft_wcharlen(c);
	if (len == 1)
		return (write(1, &c, 1));
	else if (len == 2)
	{
		s[0] = (c >> 6) | 0xc0;
		s[1] = (c & 0x3f) | 0x80;
	}
	else if (len == 3)
	{
		s[0] = (c >> 12) | 0xe0;
		s[1] = ((c >> 6) & 0x3f) | 0x80;
		s[2] = (c & 0x3f) | 0x80;
	}
	else if (len == 4)
	{
		s[0] = (c >> 18) | 0xf0;
		s[1] = ((c >> 12) & 0x3f) | 0x80;
		s[2] = ((c >> 6) & 0x3f) | 0x80;
		s[3] = (c & 0x3f) | 0x80;
	}
	return (write(1, s, len));
}

int	print_ws(wchar_t *ws, int len)
{
	int i;
	int ret;

	if (!ws)
		return (write(1, "(null)", len));
	i = -1;
	ret = 0;
	while (ws[++i])
		ret += ft_putwchar(ws[i]);
	return (ret);
}

int	ft_wcharlen(int c)
{
	if (c < 128)
		return (1);
	else if (c < 2048)
		return (2);
	else if (c < 65536)
		return (3);
	else if (c < 1114112)
		return (4);
	return (0);
}

int	ft_wstrlen_pf(const wchar_t *str)
{
	int i;
	int len;

	if (!str)
		return (6);
	i = -1;
	len = 0;
	while (str[++i])
		len += ft_wcharlen(str[i]);
	return (len);
}
