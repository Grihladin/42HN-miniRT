/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:50:20 by psenko            #+#    #+#             */
/*   Updated: 2024/10/13 13:47:42 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	dst_len = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (size > 0)
	{
		while ((*dst != '\0') && (size > 0))
		{
			dst_len++;
			dst++;
			size--;
		}
		while ((size > 1) && (*src != '\0'))
		{
			*dst++ = *src++;
			size--;
		}
		if (size > 0)
			*dst = '\0';
	}
	return (src_len + dst_len);
}
