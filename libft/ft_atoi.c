/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:29:46 by psenko            #+#    #+#             */
/*   Updated: 2024/11/01 12:38:06 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*skip_tabs(const char *s)
{
	while ((*s != '\0') && ((*s == ' ') || (*s == '\t')
			|| (*s == '\n') || (*s == '\v')
			|| (*s == '\f') || (*s == '\r')))
		s++;
	return (s);
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	minus;

	res = 0;
	minus = 1;
	nptr = skip_tabs(nptr);
	if (*nptr == '-')
	{
		minus = -1;
		nptr++;
	}
	else if (*nptr == '+')
	{
		nptr++;
		minus = 1;
	}
	while ((*nptr != '\0') && (*nptr >= 48) && (*nptr <= 57))
	{
		res *= 10;
		res += (((int)*nptr) - 48) * minus;
		nptr++;
	}
	return (res);
}
