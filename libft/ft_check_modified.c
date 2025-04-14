/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_modified.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:31:21 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 09:56:47 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_null_minus(const char **str, t_format *type)
{
	if (**str == '0')
	{
		type->zero = 1;
		type->ch = '0';
		while (**str == '0')
			(*str)++;
	}
	else if (**str == '-')
	{
		type->minus = 1;
		while (**str == '-')
			(*str)++;
	}
}

void	check_space(const char **str, t_format *type)
{
	if (**str == ' ')
	{
		type->space = 1;
		(*str)++;
	}
}

void	check_plus(const char **str, t_format *type)
{
	if (**str == '+')
	{
		type->plus = 1;
		(*str)++;
	}
}

char	check_dot(const char **str)
{
	if (**str == '.')
	{
		(*str)++;
		return (1);
	}
	return (0);
}

int	get_num(const char **str)
{
	int		num;

	num = 0;
	if ((**str >= '0') && (**str <= '9'))
	{
		while ((**str >= '0') && (**str <= '9'))
		{
			num *= 10;
			num += ((**str) - 48);
			(*str)++;
		}
	}
	return (num);
}
