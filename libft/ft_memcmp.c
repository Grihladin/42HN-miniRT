/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:46:54 by psenko            #+#    #+#             */
/*   Updated: 2024/10/12 19:36:46 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	register unsigned char		*s1_ch;
	register unsigned char		*s2_ch;

	if (n == 0)
		return (0);
	s1_ch = (unsigned char *) s1;
	s2_ch = (unsigned char *) s2;
	n--;
	while (n && (*s1_ch == *s2_ch))
	{
		s1_ch++;
		s2_ch++;
		n--;
	}
	return (*s1_ch - *s2_ch);
}
