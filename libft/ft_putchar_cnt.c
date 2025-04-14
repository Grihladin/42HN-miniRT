/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_cnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:22:19 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 09:53:11 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_cnt(char c, int fd, int *cnt)
{
	if (write(fd, &c, 1) != 1)
		return (-1);
	(*cnt)++;
	return (1);
}

int	ft_putchar_cnt_typ(char c, int fd, int *cnt, t_format *type)
{
	if (write(fd, &c, 1) != 1)
		return (-1);
	(*cnt)++;
	(type->minlen)--;
	return (1);
}

int	ft_putchar_typ(char c, int fd, int *cnt, t_format *type)
{
	if (type->minus == 1)
		if (ft_putchar_cnt(c, fd, cnt) != 1)
			return (-1);
	while ((type->minlen - 1) > 0)
	{
		if ((ft_putchar_cnt_typ(' ', fd, cnt, type) != 1))
			return (-1);
	}
	if (type->minus == 0)
		if ((ft_putchar_cnt(c, fd, cnt) != 1))
			return (-1);
	return (type->cnt_skip);
}

int	ft_putpr_cnt(int *cnt, t_format *type)
{
	if (type->minus)
		if ((ft_putchar_cnt_typ('%', 1, cnt, type) != 1))
			return (-1);
	while (type->minlen > (!type->minus))
		if ((ft_putchar_cnt_typ(' ', 1, cnt, type) != 1))
			return (-1);
	if (!type->minus)
		if ((ft_putchar_cnt_typ('%', 1, cnt, type) != 1))
			return (-1);
	return (type->cnt_skip);
}
