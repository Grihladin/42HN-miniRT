/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:13:52 by mratke            #+#    #+#             */
/*   Updated: 2025/07/06 01:13:36 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	intersect_cylinder(t_ray ray, t_cylinder *cylinder, float *t,
		t_hit_info *hit)
{
	t_hit_info	closest_hit;
	t_hit_info	body_hit;
	t_hit_info	top_cap_hit;
	t_hit_info	bottom_cap_hit;
	float		closest_t;
	closest_t = INFINITY;
	closest_hit.hit = false;
	
	body_hit = intersect_cylinder_body(ray, cylinder);
	if (body_hit.hit && body_hit.t > EPSILON && body_hit.t < closest_t)
	{
		closest_hit = body_hit;
		closest_t = body_hit.t;
	}
	top_cap_hit = intersect_cylinder_cap(ray, cylinder, true);
	if (top_cap_hit.hit && top_cap_hit.t > EPSILON && top_cap_hit.t < closest_t)
	{
		closest_hit = top_cap_hit;
		closest_t = top_cap_hit.t;
	}
	bottom_cap_hit = intersect_cylinder_cap(ray, cylinder, false);
	if (bottom_cap_hit.hit && bottom_cap_hit.t > EPSILON && bottom_cap_hit.t < closest_t)
	{
		closest_hit = bottom_cap_hit;
		closest_t = bottom_cap_hit.t;
	}
	if (closest_hit.hit)
	{
		*t = closest_t;
		hit->point = closest_hit.point;
		hit->normal = closest_hit.normal;
		return (true);
	}
	return (false);
}


