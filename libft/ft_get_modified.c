/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_modified.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:19:29 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 09:58:26 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_modified_x(const char *str, t_format *type)
{
	check_null_minus(&str, type);
	check_hash(&str, type);
	check_null_minus(&str, type);
	type->minlen = get_num(&str);
	if (check_dot(&str) == 1)
	{
		type->dot = 1;
		type->maxlen = 0;
		type->maxlen = get_num(&str);
	}
	if (*str != type->typ)
		type->err = 1;
	if ((type->minlen && (type->maxlen == 0)) || type->dot)
	{
		type->ch = ' ';
		type->zero = 0;
	}
}

void	get_modified_id(const char *str, t_format *type)
{
	check_plus(&str, type);
	check_space(&str, type);
	check_null_minus(&str, type);
	check_space(&str, type);
	check_plus(&str, type);
	type->minlen = get_num(&str);
	if (check_dot(&str) == 1)
	{
		type->dot = 1;
		type->maxlen = 0;
		type->maxlen = get_num(&str);
	}
	if (*str != type->typ)
		type->err = 1;
	if ((type->minlen && (type->maxlen == 0)) || type->dot)
	{
		type->ch = ' ';
		type->zero = 0;
	}
}

void	get_modified_str(const char *str, t_format *type)
{
	check_space(&str, type);
	check_minus(&str, type);
	check_space(&str, type);
	type->minlen = get_num(&str);
	if (check_dot(&str) == 1)
		type->maxlen = get_num(&str);
	if ((*str != type->typ) || type->space)
		type->err = 1;
}

void	get_modified_ch(const char *str, t_format *type)
{
	check_minus(&str, type);
	type->minlen = get_num(&str);
	if (*str != type->typ)
		type->err = 1;
}

void	get_modified_p(const char *str, t_format *type)
{
	check_minus(&str, type);
	type->minlen = get_num(&str);
	if (*str != type->typ)
		type->err = 1;
}
