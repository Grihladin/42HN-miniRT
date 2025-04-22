/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:55:59 by psenko            #+#    #+#             */
/*   Updated: 2025/04/22 15:21:23 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

bool	is_in_shadow(t_ray shadow_ray, t_list *elements, float max_t)
{
	float		t;
	t_point3	hit_point;		// What is it? Not using.
	t_point3	hit_normal;		// What is it? Not using.
	t_element	*element;

	while (elements != NULL)
	{
		element = elements->content;
		if (element->type == SPHERE)
		{
			if (intersect_sphere(shadow_ray, element->params, &t, &hit_point, &hit_normal))
			{
				if (t < max_t)
					return (true);
			}
		}
		else if (element->type == CYLINDER)
		{
			if (intersect_cylinder(shadow_ray, element->params, &t, &hit_point, &hit_normal))
			{
				if (t > 0.001f && t < max_t)
					return (true);
			}
		}
		else if (element->type == PLANE)
		{
			if (intersect_plane(shadow_ray, element->params, &t, &hit_point, &hit_normal))
			{
				if (t < max_t)
					return (true);
			}
		}
		elements = elements->next;
	}
	return (false);
}
