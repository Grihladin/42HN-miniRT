/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:51:38 by psenko            #+#    #+#             */
/*   Updated: 2024/10/17 13:33:13 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	check_char(char ch, char const *set)
{
	while (*set != '\0')
	{
		if (ch == *set)
			return (1);
		set++;
	}
	return (0);
}

static size_t	ft_strlen_tr(const char **s, char const *set)
{
	size_t		cnt;
	char const	*s1;
	char const	*s_end;

	cnt = 0;
	while (check_char(**s, set))
		(*s)++;
	s_end = *s;
	s1 = *s;
	while (*s_end != '\0')
		s_end++;
	s_end--;
	while (check_char(*s_end, set))
		s_end--;
	while (s1 <= s_end)
	{
		s1++;
		cnt++;
	}
	return (cnt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len;
	char		*newstr;
	char		*newstr1;

	len = ft_strlen_tr(&s1, set);
	newstr = malloc(len + 1);
	if (newstr != NULL)
	{
		newstr1 = newstr;
		while (len > 0)
		{
			*newstr1++ = *s1++;
			len--;
		}
		*newstr1 = '\0';
	}
	return (newstr);
}
