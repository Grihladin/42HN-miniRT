/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:46:40 by psenko            #+#    #+#             */
/*   Updated: 2024/10/12 19:36:42 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	register unsigned char		*s_ch;
	register unsigned char		ch;

	s_ch = (unsigned char *) s;
	ch = (unsigned char) c;
	while (n)
	{
		if (*s_ch == ch)
			return (s_ch);
		s_ch++;
		n--;
	}
	return (NULL);
}
