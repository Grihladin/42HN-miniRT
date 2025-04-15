/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:23:12 by mratke            #+#    #+#             */
/*   Updated: 2025/04/15 17:18:26 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	paint_sphere(t_vars *vars)
{
	t_list		*current;
	t_element	*element;
	t_sphere	*sphere;
	t_camera	*camera;

	current = vars->elements;
	element = current->content;
	while (element->type != SPHERE)
	{
		current = current->next;
		element = current->content;
	}
	sphere = element->params;
	//////////////////
	current = vars->elements;
	element = current->content;
	while (element->type != CAMERA)
	{
		current = current->next;
		element = current->content;
	}
	camera = element->params;
	t_ray ray;
	t_vector3 forward = camera->orient_vector;
	t_vector3 right = vec3_cross(forward, camera->orient_vector);
	camera.
	
}
