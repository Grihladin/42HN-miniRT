/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru_cnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:53:37 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 09:53:17 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_uint_len(unsigned int num, t_format *type)
{
	int	len;

	if ((num == 0) && (type->maxlen == 0))
		return (0);
	len = 1;
	while (num > 9)
	{
		num /= 10;
		len++;
	}
	if (((type->maxlen < len) && (type->dot == 0))
		|| ((type->maxlen < len) && (num != 0)))
		type->maxlen = len;
	return (len);
}

int	ft_putnbru_out(unsigned int n, int base, int hex_case, int *cnt)
{
	unsigned int	div;
	unsigned char	rest;

	div = n / base;
	rest = (char)((unsigned int) n % base) + 48;
	if (rest > 57)
		rest += hex_case;
	if (div != 0)
	{
		if (ft_putnbru_out(div, base, hex_case, cnt) != 1)
			return (-1);
	}
	if (ft_putchar_cnt(rest, 1, cnt) != 1)
		return (-1);
	return (1);
}

int	ft_putnbru_cnt(unsigned int n, int *cnt, t_format *type)
{
	int		len;

	len = get_uint_len(n, type);
	if (type->minus == 0)
		while (type->minlen > type->maxlen)
			if (ft_putchar_cnt_typ(type->ch, 1, cnt, type) != 1)
				return (-1);
	while (type->maxlen > len)
	{
		if (ft_putchar_cnt_typ('0', 1, cnt, type) != 1)
			return (-1);
		type->maxlen--;
	}
	if (!((n == 0) && (type->dot == 1) && (type->maxlen < 1)))
	{
		if (ft_putnbru_out(n, 10, 39, cnt) != 1)
			return (-1);
		type->minlen -= len;
	}
	if (type->minus == 1)
		while (type->minlen > 0)
			if (ft_putchar_cnt_typ(' ', 1, cnt, type) != 1)
				return (-1);
	return (type->cnt_skip);
}
