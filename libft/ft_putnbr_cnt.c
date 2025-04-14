/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_cnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:57:50 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 10:11:35 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_int_len(int num, t_format *type)
{
	int	len;

	if ((num == 0) && (type->maxlen == 0))
		return (0);
	len = 1;
	while ((num > 9) || (num < -9))
	{
		num /= 10;
		len++;
	}
	if (((type->maxlen < len) && (type->dot == 0))
		|| ((type->maxlen < len) && (num != 0)))
		type->maxlen = len;
	if (num < 0)
	{
		type->plus = 0;
		type->negative = 1;
	}
	return (len);
}

static int	ft_itoa_rec(int n, int *cnt)
{
	int				div;
	unsigned char	rest;
	int				minus;

	minus = 1;
	if (n < 0)
		minus = -1;
	div = n / 10;
	rest = ((char)(((int)n % 10) * (int)minus)) + 48;
	if (div != 0)
		if (ft_itoa_rec(div, cnt) != 1)
			return (-1);
	if (ft_putchar_cnt(rest, 1, cnt) != 1)
		return (-1);
	return (1);
}

static int	ft_putnbr_left(int n, int *cnt, t_format *type, int int_len)
{
	if (n < 0)
	{
		if (ft_putchar_cnt_typ('-', 1, cnt, type) != 1)
			return (-1);
	}
	else if (type->plus == 1)
		if (ft_putchar_cnt_typ('+', 1, cnt, type) != 1)
			return (-1);
	while (type->maxlen > int_len)
	{
		if (ft_putchar_cnt_typ('0', 1, cnt, type) != 1)
			return (-1);
		type->maxlen--;
	}
	if (!((n == 0) && (type->dot == 1) && (type->maxlen < 1)))
		if (ft_itoa_rec(n, cnt) != 1)
			return (-1);
	while (type->minlen > int_len)
		if (ft_putchar_cnt_typ(type->ch, 1, cnt, type) != 1)
			return (-1);
	return (type->cnt_skip);
}

static int	ft_putnbr_right(int n, int *cnt, t_format *type, int int_len)
{
	while ((type->minlen - type->plus - type->negative) > (type->maxlen))
		if (ft_putchar_cnt_typ(type->ch, 1, cnt, type) != 1)
			return (-1);
	if (type->zero == 0)
	{
		if (n < 0)
		{
			if (ft_putchar_cnt_typ('-', 1, cnt, type) != 1)
				return (-1);
		}
		else if (type->plus == 1)
			if (ft_putchar_cnt_typ('+', 1, cnt, type) != 1)
				return (-1);
	}
	while (type->maxlen > int_len)
	{
		if (ft_putchar_cnt_typ('0', 1, cnt, type) != 1)
			return (-1);
		type->maxlen--;
	}
	if (!((n == 0) && (type->dot == 1) && (type->maxlen < 1)))
		if (ft_itoa_rec(n, cnt) != 1)
			return (-1);
	return (type->cnt_skip);
}

int	ft_putnbr_cnt(int n, int *cnt, t_format *type)
{
	int		int_len;

	int_len = get_int_len(n, type);
	if ((type->space == 1) && (type->plus == 0) && (n >= 0))
		if (ft_putchar_cnt_typ(' ', 1, cnt, type) != 1)
			return (-1);
	if (type->minus)
		return (ft_putnbr_left(n, cnt, type, int_len));
	else
	{
		if (type->zero)
		{
			if (n < 0)
			{
				if (ft_putchar_cnt('-', 1, cnt) != 1)
					return (-1);
			}
			else if (type->plus == 1)
				if (ft_putchar_cnt('+', 1, cnt) != 1)
					return (-1);
		}
		return (ft_putnbr_right(n, cnt, type, int_len));
	}
}
