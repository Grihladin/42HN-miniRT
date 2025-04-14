/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:02:09 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 10:01:08 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_var(const char *src_str, va_list *var_list, int *cnt)
{
	t_format	type;

	if (ft_get_format(src_str, &type) != 1)
		return (-1);
	if (type.typ == 'c')
		return (ft_putchar_typ(va_arg(*var_list, int), 1, cnt, &type));
	else if (type.typ == 's')
		return (ft_putstr_typ(va_arg(*var_list, char *), 1, cnt, &type));
	else if (type.typ == 'p')
		return (ft_put_pointer_cnt(va_arg(*var_list, void *), 1, cnt, &type));
	else if ((type.typ == 'i') || (type.typ == 'd'))
		return (ft_putnbr_cnt(va_arg(*var_list, int), cnt, &type));
	else if (type.typ == 'u')
		return (ft_putnbru_cnt(va_arg(*var_list, unsigned int), cnt, &type));
	else if ((type.typ == 'x') || (type.typ == 'X'))
		return (ft_putnbrx_cnt(va_arg(*var_list, unsigned int), cnt, &type));
	else if (type.typ == '%')
		return (ft_putpr_cnt(cnt, &type));
	else
		return (-1);
}

int	ft_printf(const char *src, ...)
{
	const char		*src_str;
	int				cnt;
	va_list			var_list;
	int				skip;

	src_str = src;
	cnt = 0;
	va_start(var_list, src);
	while (*src_str != '\0')
	{
		if (*src_str == '%')
		{
			skip = put_var((++src_str), &var_list, &cnt);
			if (skip < 0)
				return (-1);
			src_str += skip;
		}
		else
		{
			if (ft_putchar_cnt(*src_str, 1, &cnt) != 1)
				return (-1);
			src_str++;
		}
	}
	return (va_end(var_list), cnt);
}
