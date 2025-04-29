/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:23:12 by mratke            #+#    #+#             */
/*   Updated: 2025/04/29 19:26:25 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

// GImbal lock solved
static t_ray	calculate_ray(t_vars *vars, float pixel_x, float pixel_y,
		t_vec3 initial_up)
{
	t_ray	ray;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	temp_up;

	forward = vec3_norm(vars->scene.camera->direction);
	initial_up = vec3_norm(vars->scene.camera->up);
	if (fabs(vec3_dot(forward, initial_up)) > 0.999f)
	{
		if (fabs(forward.z) > 0.999f)
			temp_up = vec3_create(0.0f, 1.0f, 0.0f);
		else
			temp_up = vec3_create(0.0f, 0.0f, 1.0f);
	}
	else
		temp_up = initial_up;
	right = vec3_norm(vec3_cross(forward, temp_up));
	up = vec3_cross(right, forward);
	ray.origin = vars->scene.camera->position;
	ray.dir = vec3_norm(vec3_sum(forward,
				vec3_sum(vec3_multiply(right, pixel_x), vec3_multiply(up,
						pixel_y))));
	return (ray);
}

t_ray	primary_ray(t_vars *vars, int i, int j)
{
	float	pixel_x;
	float	pixel_y;
	float	fov_scale;
	t_ray	ray;

	fov_scale = tanf(vars->scene.camera->field_of_view * 0.5f * M_PI / 180.0f);
	pixel_x = (2.0f * ((i + 0.5f) / vars->width) - 1.0f) * fov_scale
		* vars->aspect_ratio;
	pixel_y = (1.0f - 2.0f * ((j + 0.5f) / vars->height)) * fov_scale;
	ray = calculate_ray(vars, pixel_x, pixel_y, vars->scene.camera->up);
	return (ray);
}

static bool	sphere_equation(float a, float b, float c, float *t)
{
	float	t0;
	float	t1;
	float	discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (false);
	}
	t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
	t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (t0 > EPSILON)
	{
		*t = t0;
	}
	else if (t1 > EPSILON)
	{
		*t = t1;
	}
	else
	{
		return (false);
	}
	return (true);
}

bool	intersect_sphere(t_ray ray, t_sphere *sphere, float *t, t_hit_info *hit)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;

	oc = vec3_substract(ray.origin, sphere->center);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2.0f * vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	if (!sphere_equation(a, b, c, t))
	{
		return (false);
	}
	hit->point = vec3_sum(ray.origin, vec3_multiply(ray.dir, *t));
	hit->normal = vec3_norm(vec3_substract(hit->point, sphere->center));
	return (true);
}

void	sphere_calculation(t_vars *vars, t_sphere *sphere, int i, int j)
{
	t_ray		p_ray;
	float		t;
	t_hit_info	p;
	t_hit_info	hit;

	p_ray = primary_ray(vars, i, j);
	if (intersect_sphere(p_ray, sphere, &t, &p))
	{
		if (t > EPSILON && t < vars->frmbuf[j * vars->width + i].dist)
		{
			hit.point = p.point;
			if (vec3_dot(p_ray.dir, p.normal) > 0)
			{
				hit.normal = vec3_multiply(p.normal, -1.0f);
			}
			else
			{
				hit.normal = p.normal;
			}
			vars->frmbuf[j * vars->width + i].color3 = calculate_lighting(vars,
					hit, sphere->material, p_ray);
			vars->frmbuf[j * vars->width + i].dist = t;
		}
	}
}
