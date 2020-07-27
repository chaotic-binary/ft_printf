/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_cs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:55:43 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/20 18:57:30 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	ft_putchar_intret(int c)
{
	return (write(1, &c, 1));
}

int	print_s(char *s, int len)
{
	if (!s)
		return (write(1, "(null)", len));
	else
		return (write(1, s, len));
}

int	ft_strlen_pf(const char *str)
{
	const char *s;

	if (!str)
		return (6);
	s = str;
	while (*s)
		++s;
	return (s - str);
}
