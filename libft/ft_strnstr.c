/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:51:18 by psenko            #+#    #+#             */
/*   Updated: 2024/10/12 19:38:13 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*big1;
	const char	*little1;
	size_t		nn;

	if (*little == '\0')
		return ((char *) big);
	while ((*big != '\0') && (len > 0))
	{
		if (*big == *little)
		{
			big1 = big;
			little1 = little;
			nn = len;
			while (nn-- && (*big1 == *little1) && (*little1 != '\0'))
			{
				big1++;
				little1++;
			}
			if (*little1 == '\0')
				return ((char *) big);
		}
		len--;
		big++;
	}
	return (NULL);
}
