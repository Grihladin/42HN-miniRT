/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:45:51 by psenko            #+#    #+#             */
/*   Updated: 2024/10/10 15:56:24 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new_lst;
	t_list		*tmp_node;
	void		*tmp_cont;

	new_lst = NULL;
	while (lst != NULL)
	{
		tmp_cont = (*f)(lst->content);
		tmp_node = ft_lstnew(tmp_cont);
		if (tmp_node == NULL)
		{
			(*del)(tmp_cont);
			ft_lstclear(&new_lst, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new_lst, tmp_node);
		lst = lst->next;
	}
	return (new_lst);
}
