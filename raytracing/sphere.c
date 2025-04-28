/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:23:12 by mratke            #+#    #+#             */
/*   Updated: 2025/04/28 20:52:28 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static t_ray	calculate_ray(t_vars *vars, float pixel_x, float pixel_y)
{
	t_ray	ray;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = vec3_normalize(vars->scene.camera->direction);
	right = vec3_normalize(vec3_cross(forward, vars->scene.camera->up));
	up = vec3_cross(right, forward);
	ray.origin = vars->scene.camera->position;
	ray.direction = vec3_normalize(vec3_sum(forward,
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
	ray = calculate_ray(vars, pixel_x, pixel_y);
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
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0f * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	if (!sphere_equation(a, b, c, t))
	{
		return (false);
	}
	hit->point = vec3_sum(ray.origin, vec3_multiply(ray.direction, *t));
	hit->normal = vec3_normalize(vec3_substract(hit->point, sphere->center));
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
			if (vec3_dot(p_ray.direction, p.normal) > 0)
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
