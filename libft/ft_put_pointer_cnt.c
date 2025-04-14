/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pointer_cnt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:53:43 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 10:01:42 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_point_len(unsigned long int n)
{
	int	len;

	len = 1;
	while (n > 15)
	{
		n /= 16;
		len++;
	}
	return (len);
}

static int	ft_put_pointer_fd_rec(unsigned long int n, int fd, int *cnt)
{
	unsigned long int	div;
	unsigned char		rest;

	div = n / 16;
	rest = (char)((unsigned long int) n % 16) + 48;
	if (rest > 57)
		rest += 39;
	if (div != 0)
		if (ft_put_pointer_fd_rec(div, fd, cnt) != 1)
			return (-1);
	if (write(fd, &rest, 1) != 1)
		return (-1);
	(*cnt)++;
	return (1);
}

int	ft_put_pointer_cnt(void *pnt, int fd, int *cnt, t_format *type)
{
	int		pnt_len;

	pnt_len = get_point_len((unsigned long int) pnt) + 2;
	if (type->minus == 1)
	{
		if (ft_putstr_cnt("0x", fd, cnt) != 1)
			return (-1);
		if (ft_put_pointer_fd_rec((unsigned long int) pnt, 1, cnt) != 1)
			return (-1);
	}
	while ((type->minlen - pnt_len) > 0)
	{
		if ((ft_putchar_cnt_typ(' ', fd, cnt, type) != 1))
			return (-1);
	}
	if (type->minus == 0)
	{
		if (ft_putstr_cnt("0x", fd, cnt) != 1)
			return (-1);
		if (ft_put_pointer_fd_rec((unsigned long int) pnt, 1, cnt) != 1)
			return (-1);
	}
	return (type->cnt_skip);
}
