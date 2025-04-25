/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:55:59 by psenko            #+#    #+#             */
/*   Updated: 2025/04/25 16:56:17 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

bool	is_in_shadow(t_ray shadow_ray, t_list *elements, float max_t)
{
	float		t;
	t_element	*element;
	t_point3	hit_point;
	t_point3	hit_normal;
	t_hit_info	hit;

	while (elements != NULL)
	{
		element = elements->content;
		if ((element->type == SPHERE)
			&& (intersect_sphere(shadow_ray, element->params, &t, &hit)) && (t > EPSILON) && (t < max_t))
			return (true);
		else if ((element->type == CYLINDER)
			&& (intersect_cylinder(shadow_ray, element->params, &t, &hit_point,
					&hit_normal)) && (t > EPSILON) && (t < max_t))
			return (true);
		else if ((element->type == PLANE)
			&& (intersect_plane(shadow_ray, element->params, &t, &hit_point,
					&hit_normal)) && (t > EPSILON) && (t < max_t))
			return (true);
		elements = elements->next;
	}
	return (false);
}
