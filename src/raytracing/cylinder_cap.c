/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:02:51 by mratke            #+#    #+#             */
/*   Updated: 2025/07/06 01:13:03 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	intersect_plane_cyl(t_ray ray, t_point3 plane_point,
		t_vec3 plane_normal, float *t)
{
	float	denom;

	denom = vec3_dot(ray.dir, plane_normal);
	if (fabsf(denom) < EPSILON)
		return (false);
	*t = vec3_dot(vec3_substract(plane_point, ray.origin), plane_normal) / denom;
	return (*t > EPSILON);
}

static t_hit_info	calculate_cap_vector(t_ray ray, t_cylinder *cylinder,
		t_point3 cap_center, t_vec3 cap_normal)
{
	t_hit_info	hit_info;
	float		radius;
	t_point3	hit_point_cap;
	t_vec3		vec_to_hit;
	float		t_cap;

	hit_info.hit = false;
	hit_info.t = INFINITY;
	radius = cylinder->diameter / 2.0f;
	if (intersect_plane_cyl(ray, cap_center, cap_normal, &t_cap))
	{
		hit_point_cap = vec3_sum(ray.origin, vec3_multiply(ray.dir,
					t_cap));
		vec_to_hit = vec3_substract(hit_point_cap, cap_center);
		if (vec3_dot(vec_to_hit, vec_to_hit) <= radius * radius)
		{
			hit_info.hit = true;
			hit_info.t = t_cap;
			hit_info.point = hit_point_cap;
			hit_info.normal = cap_normal;
		}
	}
	return (hit_info);
}

t_hit_info	intersect_cylinder_cap(t_ray ray, t_cylinder *cylinder,
		bool is_top_cap)
{
	t_hit_info	hit_info;
	t_vec3		axis;
	float		half_h;
	t_point3	cap_center;
	t_vec3		cap_normal;

	axis = cylinder->norm_vec_axis_cyl;
	half_h = cylinder->height / 2.0f;
	if (is_top_cap)
	{
		cap_center = vec3_sum(cylinder->coord_center, vec3_multiply(axis,
					half_h));
		cap_normal = axis;
	}
	else
	{
		cap_center = vec3_sum(cylinder->coord_center, vec3_multiply(axis,
					-half_h));
		cap_normal = vec3_multiply(axis, -1.0f);
	}
	hit_info = calculate_cap_vector(ray, cylinder, cap_center, cap_normal);
	return (hit_info);
}
