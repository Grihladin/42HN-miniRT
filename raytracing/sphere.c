/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:23:12 by mratke            #+#    #+#             */
/*   Updated: 2025/07/06 01:16:55 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static bool g_cache_valid = false;

static void	update_camera_cache(t_vars *vars)
{
	t_vec3	initial_up;
	t_vec3	temp_up;

	vars->cam_cache.forward = vec3_norm(vars->scene.camera->direction);
	initial_up = vec3_norm(vars->scene.camera->up);
	if (fabs(vec3_dot(vars->cam_cache.forward, initial_up)) > 0.999f)
	{
		if (fabs(vars->cam_cache.forward.z) > 0.999f)
			temp_up = vec3_create(0.0f, 1.0f, 0.0f);
		else
			temp_up = vec3_create(0.0f, 0.0f, 1.0f);
	}
	else
		temp_up = initial_up;
	vars->cam_cache.right = vec3_norm(vec3_cross(vars->cam_cache.forward, temp_up));
	vars->cam_cache.up = vec3_cross(vars->cam_cache.right, vars->cam_cache.forward);
	vars->cam_cache.fov_scale = tanf(vars->scene.camera->field_of_view * 0.5f * M_PI / 180.0f);
}

t_ray	primary_ray(t_vars *vars, int i, int j)
{
	float	pixel_x;
	float	pixel_y;
	t_ray	ray;
	
	if (!g_cache_valid)
	{
		update_camera_cache(vars);
		g_cache_valid = true;
	}
	pixel_x = (2.0f * ((i + 0.5f) / vars->width) - 1.0f) * vars->cam_cache.fov_scale * vars->aspect_ratio;
	pixel_y = (1.0f - 2.0f * ((j + 0.5f) / vars->height)) * vars->cam_cache.fov_scale;
	ray.origin = vars->scene.camera->position;
	ray.dir = vec3_norm(vec3_sum(vars->cam_cache.forward,
				vec3_sum(vec3_multiply(vars->cam_cache.right, pixel_x), 
					vec3_multiply(vars->cam_cache.up, pixel_y))));
	return (ray);
}

static bool	sphere_equation(float a, float b, float c, float *t)
{
	float	discriminant;
	float	sqrt_discriminant;
	float	t0, t1;

	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return (false);
	sqrt_discriminant = sqrtf(discriminant);
	t0 = (-b - sqrt_discriminant) / (2.0f * a);
	t1 = (-b + sqrt_discriminant) / (2.0f * a);
	if (t0 > EPSILON)
		*t = t0;
	else if (t1 > EPSILON)
		*t = t1;
	else
		return (false);
	return (true);
}

bool	intersect_sphere(t_ray ray, t_sphere *sphere, float *t, t_hit_info *hit)
{
	t_vec3	oc;
	float	a, b, c;
	float	radius_sq;
	
	oc = vec3_substract(ray.origin, sphere->center);
	radius_sq = sphere->radius * sphere->radius;
	a = vec3_dot(ray.dir, ray.dir);
	b = 2.0f * vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - radius_sq;
	if (!sphere_equation(a, b, c, t))
		return (false);
	hit->point = vec3_sum(ray.origin, vec3_multiply(ray.dir, *t));
	hit->normal = vec3_norm(vec3_substract(hit->point, sphere->center));
	return (true);
}

void	invalidate_camera_cache(t_vars *vars)
{
	(void)vars;
	g_cache_valid = false;
}
