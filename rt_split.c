/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:48:55 by psenko            #+#    #+#             */
/*   Updated: 2025/04/14 14:13:04 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_space(char str)
{
	if ((str != '\0') && ((str == ' ') || (str == '\t') || (str == '\n')
			|| (str == '\v') || (str == '\f') || (str == '\r')))
		return (1);
	return (0);
}

static int	str_size(char *str)
{
	int		size;

	size = 0;
	while ((*str != '\0') && (is_space(*str) == 0))
	{
		size++;
		str++;
	}
	return (size);
}

static char	*get_next_part(char **str)
{
	char	*new_str;
	int		size;

	new_str = NULL;
	size = str_size(*str);
	new_str = ft_calloc(size + 1, 1);
	if (new_str != NULL)
		ft_strlcpy(new_str, *str, size + 1);
	*str += size;
	return (new_str);
}

// static char	*mv_lst_to_str(t_list *lst)
// {
// 	t_list	*tmp_lst;
// 	char	*result_str;
// 	size_t	strsize;

// 	result_str = NULL;
// 	tmp_lst = lst;
// 	strsize = 0;
// 	while (tmp_lst != NULL)
// 	{
// 		strsize += ft_strlen((char *)tmp_lst->content);
// 		tmp_lst = tmp_lst->next;
// 	}
// 	result_str = ft_calloc(strsize + 1, sizeof(char));
// 	if (result_str == NULL)
// 		return (free_list(lst), NULL);
// 	tmp_lst = lst;
// 	while (tmp_lst != NULL)
// 	{
// 		ft_strlcat(result_str, (char *)tmp_lst->content, strsize + 1);
// 		tmp_lst = tmp_lst->next;
// 	}
// 	ft_lstclear(lst, free);
// 	return (result_str);
// }

t_list	*rt_split(char *str)
{
	char	*new_str;
	t_list	*str_list;
	t_list	*tmp;

	str_list = NULL;
	new_str = NULL;
	while (*str != '\0')
	{
		while (is_space(*str))
			str++;
		if (*str != '\0')
		{
			new_str = get_next_part(&str);
			if (new_str == NULL)
				return (ft_lstclear(&str_list, free), NULL);
			tmp = ft_lstnew(new_str);
			if (tmp == NULL)
				return (ft_lstclear(&tmp, free), NULL);
			ft_lstadd_back(&str_list, tmp);
		}
	}
	return (str_list);
}
