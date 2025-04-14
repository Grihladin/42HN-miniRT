/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:47:07 by psenko            #+#    #+#             */
/*   Updated: 2024/10/12 19:36:50 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*dest_ch;
	const char		*src_ch;

	if ((dest == NULL) && (src == NULL))
		return (dest);
	dest_ch = dest;
	src_ch = src;
	while (n)
	{
		*dest_ch = *src_ch;
		dest_ch++;
		src_ch++;
		n--;
	}
	return (dest);
}
