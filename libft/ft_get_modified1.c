/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_modified1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:58:07 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 09:58:29 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_modified_u(const char *str, t_format *type)
{
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

void	get_modified_pr(const char *str, t_format *type)
{
	check_null_minus(&str, type);
	check_null_minus(&str, type);
	type->minlen = get_num(&str);
	if (*str != type->typ)
		type->err = 1;
}
