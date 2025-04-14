/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:48:55 by psenko            #+#    #+#             */
/*   Updated: 2024/11/01 12:38:22 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	int_length(int n)
{
	char	length;

	if (n == 0)
		return (1);
	length = 0;
	if (n < 0)
		length++;
	while (n != 0)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

static char	*ft_itoa_rec(char *dest, int n, int minus)
{
	int		div;
	int		rest;

	div = n / 10;
	rest = (n % 10) * minus;
	if (div != 0)
		dest = ft_itoa_rec(dest, div, minus);
	*dest = rest + 48;
	return (dest + 1);
}

char	*ft_itoa(int n)
{
	char	*dest;
	char	*dest1;
	int		minus;

	minus = 1;
	dest = malloc(int_length(n) + 1);
	if (dest != NULL)
	{
		dest1 = dest;
		if (n < 0)
		{
			*dest1++ = '-';
			minus = -1;
		}
		dest1 = ft_itoa_rec(dest1, n, minus);
		*dest1 = '\0';
	}
	return (dest);
}
