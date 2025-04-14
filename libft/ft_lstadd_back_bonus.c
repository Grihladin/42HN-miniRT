/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:43:45 by psenko            #+#    #+#             */
/*   Updated: 2024/10/10 14:44:18 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*cur_node;

	cur_node = *lst;
	if (cur_node == NULL)
	{
		*lst = new;
		(*lst)->next = NULL;
	}
	else
	{
		while (cur_node->next != NULL)
			cur_node = cur_node->next;
		cur_node->next = new;
	}
}
