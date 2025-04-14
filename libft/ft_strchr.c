/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:49:15 by psenko            #+#    #+#             */
/*   Updated: 2024/11/10 10:31:15 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s != NULL)
	{
		while ((*s != '\0') && ((*s != (char) c)))
			s++;
		if (*s == (char) c)
			return ((char *) s);
	}
	return (NULL);
}
