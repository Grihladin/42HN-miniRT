/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:18:37 by mratke            #+#    #+#             */
/*   Updated: 2025/04/29 19:26:25 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

bool	intersect_plane(t_ray ray, t_plane *plane, float *t, t_hit_info *hit)
{
	t_vec3	p0_l0;
	float	denom;

	denom = vec3_dot(plane->normal_vector, ray.dir);
	if (fabs(denom) < EPSILON)
	{
		return (false);
	}
	p0_l0 = vec3_substract(plane->coord_point, ray.origin);
	*t = vec3_dot(p0_l0, plane->normal_vector) / denom;
	if (*t < EPSILON)
	{
		return (false);
	}
	hit->point = vec3_sum(ray.origin, vec3_multiply(ray.dir, *t));
	hit->normal = plane->normal_vector;
	return (true);
}

void	plane_calculation(t_vars *vars, t_plane *plane, int i, int j)
{
	t_hit_info	hit;
	t_hit_info	p_hit;
	t_ray		p_ray;
	float		t;

	p_ray = primary_ray(vars, i, j);
	if (intersect_plane(p_ray, plane, &t, &p_hit))
	{
		if (t > EPSILON && t < vars->frmbuf[j * vars->width + i].dist)
		{
			hit.point = p_hit.point;
			if (vec3_dot(p_ray.dir, p_hit.normal) > 0)
			{
				hit.normal = vec3_multiply(p_hit.normal, -1.0f);
			}
			else
			{
				hit.normal = p_hit.normal;
			}
			vars->frmbuf[j * vars->width + i].color3 = calculate_lighting(vars,
					hit, plane->material, p_ray);
			vars->frmbuf[j * vars->width + i].dist = t;
		}
	}
}
