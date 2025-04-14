/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:51:28 by psenko            #+#    #+#             */
/*   Updated: 2024/10/12 19:38:16 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		*ss;

	ss = (char *) s;
	while (*ss != '\0')
		ss++;
	while (ss >= (char *) s)
	{
		if (*ss == (char) c)
			return (ss);
		ss--;
	}
	return (NULL);
}
