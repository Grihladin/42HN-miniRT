/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:56:23 by psenko            #+#    #+#             */
/*   Updated: 2025/04/17 11:59:55 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	redraw_image(t_vars *vars)
{
	t_element	*element;
	t_list		*elements;
	t_sphere	*sphere;

	elements = vars->elements;
	ft_printf("Redraw\n");
	while (elements != NULL)
	{
		element = elements->content;
		if (element->type == SPHERE)
		{
			sphere = element->params;
			raytrace(vars, sphere);
		}
		elements = elements->next;
	}
	out_image(vars);
	return (1);
}
