/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:47:21 by psenko            #+#    #+#             */
/*   Updated: 2024/10/12 19:36:53 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*dest_ch;
	const char		*src_ch;

	if ((dest == NULL) && (src == NULL))
		return (dest);
	dest_ch = dest;
	src_ch = src;
	if (dest_ch < src_ch)
	{
		while (n--)
			*dest_ch++ = *src_ch++;
	}
	else
	{
		dest_ch = dest_ch + (n - 1);
		src_ch = src_ch + (n - 1);
		while (n)
		{
			*dest_ch-- = *src_ch--;
			n--;
		}
	}
	return (dest);
}
