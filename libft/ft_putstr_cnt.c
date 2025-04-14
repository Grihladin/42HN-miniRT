/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_cnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:55:26 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 10:16:01 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_typ(char *s, int fd, int *cnt, t_format *type)
{
	int		str_len;

	if (s == NULL)
		s = "(null)";
	str_len = ft_strlen(s);
	if ((str_len > type->maxlen) && (type->maxlen > -1))
		str_len = type->maxlen;
	type->maxlen = str_len;
	if (type->minus == 1)
	{
		while (type->maxlen > 0)
		{
			if ((ft_putchar_cnt_typ(*(s++), fd, cnt, type) != 1))
				return (-1);
			type->maxlen--;
		}
	}
	while (type->minlen > type->maxlen)
		if ((ft_putchar_cnt_typ(' ', fd, cnt, type) != 1))
			return (-1);
	if (type->minus == 0)
		while (type->maxlen-- > 0)
			if ((ft_putchar_cnt_typ(*(s++), fd, cnt, type) != 1))
				return (-1);
	return (type->cnt_skip);
}

int	ft_putstr_cnt(char *s, int fd, int *cnt)
{
	if (s == NULL)
		s = "(null)";
	else
	{
		while (*s != '\0')
		{
			if (ft_putchar_cnt(*s, fd, cnt) != 1)
				return (-1);
			s++;
		}
	}
	return (1);
}
