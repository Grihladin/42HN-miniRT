/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:49:29 by psenko            #+#    #+#             */
/*   Updated: 2024/10/13 13:47:59 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t		len;
	char		*newstr;
	char		*newstr1;

	len = ft_strlen(s);
	newstr = malloc(len + 1);
	if (newstr != NULL)
	{
		newstr1 = newstr;
		while (len > 0)
		{
			*newstr1++ = *s++;
			len--;
		}
		*newstr1 = '\0';
	}
	return (newstr);
}
