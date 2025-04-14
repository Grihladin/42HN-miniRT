/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:50:31 by psenko            #+#    #+#             */
/*   Updated: 2024/10/13 13:47:37 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	while ((dstsize > 1) && (*src != '\0'))
	{
		*dst = *src;
		dstsize--;
		dst++;
		src++;
	}
	if (dstsize > 0)
		*dst = '\0';
	return (src_len);
}
