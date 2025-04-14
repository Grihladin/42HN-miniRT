/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:34:36 by psenko            #+#    #+#             */
/*   Updated: 2024/10/09 17:41:29 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char		*arr;
	unsigned char		*arr1;
	size_t				len;

	len = nmemb * size;
	arr = malloc(len);
	if (arr == NULL)
		return (NULL);
	arr1 = arr;
	while (len)
	{
		*arr1 = 0;
		arr1++;
		len--;
	}
	return (arr);
}
