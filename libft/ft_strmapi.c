/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:50:54 by psenko            #+#    #+#             */
/*   Updated: 2024/10/13 13:47:32 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	char			*dest1;
	unsigned int	cnt;

	cnt = 0;
	dest = malloc(ft_strlen(s) + 1);
	if (dest != NULL)
	{
		dest1 = dest;
		while (s[cnt] != '\0')
		{
			*dest1 = (*f)(cnt, s[cnt]);
			cnt++;
			dest1++;
		}
		*dest1 = '\0';
	}
	return (dest);
}
