/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:23:12 by mratke            #+#    #+#             */
/*   Updated: 2025/04/15 19:06:20 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	primary_ray(t_vars *vars, t_camera *camera, int i, int j)
{
	t_ray		ray;
	t_vector3	forward;
	t_vector3	right;
	t_vector3	up;
	float		fov_scale;
	float		pixel_x;
	float		pixel_y;

	forward = camera->orient_vector;
	right = vec3_cross(forward, camera->up);
	up = vec3_cross(right, forward);
	fov_scale = tanf(camera->horizont_field_degree * 0.5f * M_PI / 180.0f);
	pixel_x = (2.0f * ((i + 0.5f) / vars->width) - 1.0f) * fov_scale
		* vars->aspect_ratio;
	pixel_y = (1.0f - 2.0f * ((j + 0.5f) / vars->height)) * fov_scale;
	ray.origin = camera->view_point;
	ray.direction = vec3_normalize(vec3_sum(vec3_sum(vec3_multiply(right,
						pixel_x), vec3_multiply(up, pixel_y)), forward));
	return (ray);
}

bool	intersect_sphere(t_ray *ray, t_sphere *sphere, float *t,
		t_point *hit_point, t_vector3 *hit_normalized)
{
	t_vector3	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t0;
	float		t1;

	oc = vec3_subtract(ray->origin, sphere->coord_center);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2.0f * vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (false);
	}
	t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
	t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (t0 > 0.001f)
	{
		*t = t0;
	}
	else if (t1 > 0.001f)
	{
		*t = t1;
	}
	else
	{
		return (false); // Both intersection points are behind the ray origin
	}
	*hit_point = vec3_sum(ray->origin, vec3_multiply(ray->direction, *t));
	*hit_normalized = vec3_normalize(vec3_subtract(*hit_point,
				sphere->coord_center));
}
