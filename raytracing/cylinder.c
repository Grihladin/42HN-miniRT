/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:13:52 by mratke            #+#    #+#             */
/*   Updated: 2025/04/28 20:08:15 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

bool	intersect_cylinder(t_ray ray, t_cylinder *cylinder, float *t,
		t_hit_info *hit)
{
	t_hit_info	closest_hit;
	t_hit_info	body_hit;
	t_hit_info	top_cap_hit;
	t_hit_info	bottom_cap_hit;

	closest_hit.hit = false;
	closest_hit.t = INFINITY;
	body_hit = intersect_cylinder_body(ray, cylinder);
	if (body_hit.hit && body_hit.t < closest_hit.t)
		closest_hit = body_hit;
	top_cap_hit = intersect_cylinder_cap(ray, cylinder, true);
	if (top_cap_hit.hit && top_cap_hit.t < closest_hit.t)
		closest_hit = top_cap_hit;
	bottom_cap_hit = intersect_cylinder_cap(ray, cylinder, false);
	if (bottom_cap_hit.hit && bottom_cap_hit.t < closest_hit.t)
		closest_hit = bottom_cap_hit;
	if (closest_hit.hit)
	{
		*t = closest_hit.t;
		hit->point = closest_hit.point;
		hit->normal = closest_hit.normal;
		return (true);
	}
	return (false);
}

void	cylinder_calculation(t_vars *vars, t_cylinder *cylinder, int i, int j)
{
	t_ray		p_ray;
	float		t;
	t_hit_info	p;
	t_hit_info	hit;

	cylinder->norm_vec_axis_cyl = vec3_normalize(cylinder->norm_vec_axis_cyl);
	p_ray = primary_ray(vars, i, j);
	if (intersect_cylinder(p_ray, cylinder, &t, &p))
	{
		if (t > EPSILON && t < vars->frmbuf[j * vars->width + i].dist)
		{
			hit.point = p.point;
			if (vec3_dot(p_ray.direction, p.normal) > 0)
			{
				hit.normal = vec3_multiply(p.normal, -1.0f);
			}
			else
			{
				hit.normal = p.normal;
			}
			vars->frmbuf[j * vars->width + i].color3 = calculate_lighting(vars,
					hit, cylinder->material, p_ray);
			vars->frmbuf[j * vars->width + i].dist = t;
		}
	}
}
