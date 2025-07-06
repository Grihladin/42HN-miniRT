/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:18:37 by mratke            #+#    #+#             */
/*   Updated: 2025/07/06 01:16:34 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	intersect_plane(t_ray ray, t_plane *plane, float *t, t_hit_info *hit)
{
	t_vec3	p0_l0;
	float	denom;

	denom = vec3_dot(plane->normal_vector, ray.dir);
	if (fabsf(denom) < EPSILON)
		return (false);
	p0_l0 = vec3_substract(plane->coord_point, ray.origin);
	*t = vec3_dot(p0_l0, plane->normal_vector) / denom;
	if (*t < EPSILON)
		return (false);
	hit->point = vec3_sum(ray.origin, vec3_multiply(ray.dir, *t));
	hit->normal = plane->normal_vector;
	return (true);
}


