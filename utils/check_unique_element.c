/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unique_element.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:02:54 by psenko            #+#    #+#             */
/*   Updated: 2025/04/15 17:25:27 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	check_unique_element(t_list *elements, int type)
{
	t_element	*element;

	if ((type == AMBIENT_LIGHTNING) || (type == CAMERA) || (type == LIGHT))
	{
		while (elements != NULL)
		{
			element = elements->content;
			if (element->type == type)
				return (1);
			elements = elements->next;
		}
	}
	return (0);
}
