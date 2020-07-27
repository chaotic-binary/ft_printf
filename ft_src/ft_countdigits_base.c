/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countdigits_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 21:54:28 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/23 21:54:47 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int					countdigits_base(size_t n, size_t bs)
{
	int count;

	count = 1;
	while (n / bs != 0)
	{
		count++;
		n /= bs;
	}
	return (count);
}
