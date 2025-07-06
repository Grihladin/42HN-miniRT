/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:22:14 by psenko            #+#    #+#             */
/*   Updated: 2025/04/21 13:26:31 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	add_element_to_scene(t_vars *vars, t_element *new_element)
{
	if (new_element->type == AMBIENT_LIGHTNING)
	{
		vars->scene.amb_light = new_element->params;
		free(new_element);
	}
	else if (new_element->type == CAMERA)
	{
		vars->scene.camera = new_element->params;
		free(new_element);
	}
	else if (new_element->type == LIGHT)
	{
		vars->scene.light = new_element->params;
		free(new_element);
	}
	return (0);
}

int	add_element_to_list(t_vars *vars, t_list *element_params,
	t_element *new_element)
{
	t_list			*new_el;

	if (check_unique_element(vars, new_element->type))
	{
		free(new_element);
		return (print_error(element_params->content,
				ERR_EL_NOT_UNIQ), 1);
	}
	if ((new_element->type == AMBIENT_LIGHTNING)
		|| (new_element->type == CAMERA) || (new_element->type == LIGHT))
		add_element_to_scene(vars, new_element);
	else
	{
		new_el = ft_calloc(sizeof (t_list), 1);
		if (new_el == NULL)
			return (free(new_element), 1);
		new_el->content = new_element;
		ft_lstadd_back(&(vars->elements), new_el);
	}
	return (0);
}
