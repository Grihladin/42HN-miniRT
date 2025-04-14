/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:51:49 by psenko            #+#    #+#             */
/*   Updated: 2024/10/13 13:47:16 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	char	*newstr1;

	if (start > ft_strlen(s))
	{
		len = 0;
		start = 0;
	}
	while ((*s != '\0') && (start-- > 0))
		s++;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	newstr = malloc(len + 1);
	if (newstr != NULL)
	{
		newstr1 = newstr;
		while ((len > 0) && (*s != '\0'))
		{
			*newstr1++ = *s++;
			len--;
		}
		*newstr1 = '\0';
	}
	return (newstr);
}
