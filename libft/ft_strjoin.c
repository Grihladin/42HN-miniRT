/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:50:06 by psenko            #+#    #+#             */
/*   Updated: 2024/11/13 14:16:54 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a new string,
which is the result of the concatenation of ’s1’ and ’s2’.
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len_s1;
	size_t		len_s2;
	char		*newstr;
	char		*newstr1;

	if ((s1 != NULL) && (s2 != NULL))
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		newstr = malloc(len_s1 + len_s2 + 1);
		if (newstr != NULL)
		{
			newstr1 = newstr;
			while (*s1 != '\0')
				*newstr1++ = *s1++;
			while (*s2 != '\0')
				*newstr1++ = *s2++;
			*newstr1 = '\0';
		}
		return (newstr);
	}
	return (NULL);
}
