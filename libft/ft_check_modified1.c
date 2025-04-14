/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_modified1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:54:10 by psenko            #+#    #+#             */
/*   Updated: 2024/10/28 09:52:54 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_minus(const char **str, t_format *type)
{
	if (**str == '-')
	{
		type->minus = 1;
		while (**str == '-')
			(*str)++;
	}
}

void	check_hash(const char **str, t_format *type)
{
	if (**str == '#')
	{
		type->hash++;
		(*str)++;
	}
}
