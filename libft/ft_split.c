/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:48:55 by psenko            #+#    #+#             */
/*   Updated: 2024/11/14 14:39:26 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ch_count(char const *s, char c)
{
	size_t		cnt;
	int			new_str;

	cnt = 0;
	new_str = 1;
	while (*s != '\0')
	{
		while (*s == c)
		{
			new_str = 1;
			s++;
		}
		if (new_str && (*s != '\0'))
		{
			cnt++;
			new_str = 0;
			s++;
		}
		else if (*s != '\0')
			s++;
	}
	return (cnt);
}

static size_t	str_len_ch(char const *s, char c)
{
	size_t		len;

	len = 0;
	while ((*s != '\0') && (*s != c))
	{
		len++;
		s++;
	}
	return (len);
}

static char	**free_all(char **strings)
{
	char		**strings1;

	strings1 = strings;
	while (*strings1 != NULL)
	{
		free(*strings1);
		strings1++;
	}
	free(strings);
	strings = NULL;
	return (NULL);
}

static char	ft_strcpy_m(char **strings1, const char *src, size_t len)
{
	char	*dst;

	while (*strings1 != NULL)
		strings1++;
	*strings1 = (char *) malloc(len + 1);
	if (*strings1 == NULL)
		return (0);
	dst = *strings1;
	while (len)
	{
		*dst++ = *src++;
		len--;
	}
	*dst = '\0';
	strings1++;
	*strings1 = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**strings;
	size_t		str_cnt;
	size_t		str_len;

	str_cnt = ch_count(s, c);
	strings = (char **) malloc(sizeof(char *) * (str_cnt + 1));
	if (strings != NULL)
	{
		*strings = NULL;
		while (*s != '\0')
		{
			while (*s == c)
				s++;
			str_len = str_len_ch(s, c);
			if (str_len > 0)
				if (ft_strcpy_m(strings, s, str_len) == 0)
					return (free_all(strings));
			s += str_len;
		}
	}
	return (strings);
}
