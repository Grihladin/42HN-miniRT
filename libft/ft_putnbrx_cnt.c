/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrx_cnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:37:34 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 10:14:25 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_xint_len(unsigned int num, t_format *type)
{
	int	len;

	if ((num == 0) && (type->maxlen == 0))
		return (0);
	len = 1;
	while (num > 15)
	{
		num /= 16;
		len++;
	}
	if (((type->maxlen < len) && (type->dot == 0))
		|| ((type->maxlen < len) && (num != 0)))
		type->maxlen = len;
	return (len);
}

static int	out_pref(t_format *type, unsigned int n, int *cnt)
{
	if ((type->hash == 1) && (n != 0))
	{
		if (ft_putchar_cnt('0', 1, cnt) != 1)
			return (-1);
		if (ft_putchar_cnt(type->typ, 1, cnt) != 1)
			return (-1);
	}
	else if ((type->hash == 1) && (n == 0) && (type->minus == 0))
	{
		while (type->minlen > type->maxlen)
			if (ft_putchar_cnt_typ(type->ch, 1, cnt, type) != 1)
				return (-1);
	}
	return (0);
}

int	ft_putnbrx_left(unsigned int n, int *cnt, t_format *type, int len)
{
	while (type->maxlen > len)
	{
		if (ft_putchar_cnt_typ('0', 1, cnt, type) != 1)
			return (-1);
		type->maxlen--;
	}
	if (!((n == 0) && (type->dot == 1) && (type->maxlen < 1)))
	{
		if (type->typ == 'x')
		{
			if (ft_putnbru_out(n, 16, 39, cnt) != 1)
				return (-1);
		}
		else if (type->typ == 'X')
		{
			if (ft_putnbru_out(n, 16, 7, cnt) != 1)
				return (-1);
		}
		type->minlen -= len;
	}
	while (type->minlen > 0)
		if (ft_putchar_cnt_typ(' ', 1, cnt, type) != 1)
			return (-1);
	return (type->cnt_skip);
}

int	ft_putnbrx_right(unsigned int n, int *cnt, t_format *type, int len)
{
	if (type->ch == ' ')
		if (out_pref(type, n, cnt) == -1)
			return (-1);
	while (type->maxlen > len)
	{
		if (ft_putchar_cnt_typ('0', 1, cnt, type) != 1)
			return (-1);
		type->maxlen--;
	}
	if (!((n == 0) && (type->dot == 1) && (type->maxlen < 1)))
	{
		if (type->typ == 'x')
		{
			if (ft_putnbru_out(n, 16, 39, cnt) != 1)
				return (-1);
		}
		else if (type->typ == 'X')
		{
			if (ft_putnbru_out(n, 16, 7, cnt) != 1)
				return (-1);
		}
		type->minlen -= len;
	}
	return (type->cnt_skip);
}

int	ft_putnbrx_cnt(unsigned int n, int *cnt, t_format *type)
{
	int		len;

	len = get_xint_len(n, type);
	if (type->hash && (n != 0))
		type->minlen -= 2;
	if (type->minus == 1)
	{
		if (out_pref(type, n, cnt) == -1)
			return (-1);
		return (ft_putnbrx_left(n, cnt, type, len));
	}
	else
	{
		if (type->ch == '0')
			if (out_pref(type, n, cnt) == -1)
				return (-1);
		while (type->minlen > type->maxlen)
			if (ft_putchar_cnt_typ(type->ch, 1, cnt, type) != 1)
				return (-1);
		return (ft_putnbrx_right(n, cnt, type, len));
	}
}
