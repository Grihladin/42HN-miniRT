/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:19:07 by psenko            #+#    #+#             */
/*   Updated: 2025/04/15 10:55:37 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	delete_element(void *el)
{
	t_element		*element;

	element = el;
	free(element->params);
	free(element);
}

void	free_arr_of_str(char ***strings)
{
	char		**strings1;

	strings1 = *strings;
	while (*strings1 != NULL)
	{
		free(*strings1);
		strings1++;
	}
	free(*strings);
}
