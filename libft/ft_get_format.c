/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:58:57 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 09:57:35 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_type(t_format *type)
{
	type->typ = 0;
	type->cnt_skip = 0;
	type->hash = 0;
	type->dot = 0;
	type->minus = 0;
	type->plus = 0;
	type->space = 0;
	type->zero = 0;
	type->minlen = -1;
	type->maxlen = -1;
	type->err = 0;
	type->ch = ' ';
	type->negative = 0;
}

int	check_it_format(char ch)
{
	if ((ch == 'c') || (ch == 's') || (ch == 'p') || (ch == 'd')
		|| (ch == 'i') || (ch == 'u') || (ch == 'x')
		|| (ch == 'X') || (ch == '%'))
		return (1);
	else
		return (0);
}

void	get_format(const char *str, t_format *type)
{
	while ((check_it_format(*str) != 1) && (*str != '\0'))
	{
		type->cnt_skip++;
		str++;
	}
	if (check_it_format(*str) == 1)
	{
		type->cnt_skip++;
		type->typ = *str;
		return ;
	}
	type->err = 1;
}

int	ft_get_format(const char *str, t_format *type)
{
	init_type(type);
	get_format(str, type);
	if ((type->typ != 0) && (type->err != 1))
	{
		if ((type->typ == 'x') || (type->typ == 'X'))
			get_modified_x(str, type);
		else if ((type->typ == 'd') || (type->typ == 'i'))
			get_modified_id(str, type);
		else if (type->typ == 'u')
			get_modified_u(str, type);
		else if (type->typ == 'c')
			get_modified_ch(str, type);
		else if (type->typ == 's')
			get_modified_str(str, type);
		else if (type->typ == 'p')
			get_modified_p(str, type);
		else if (type->typ == '%')
			get_modified_pr(str, type);
		return (1);
	}
	return (-1);
}
