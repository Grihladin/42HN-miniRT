/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:23:12 by mratke            #+#    #+#             */
/*   Updated: 2025/04/23 20:46:44 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_ray	primary_ray(t_vars *vars, int i, int j)
{
	t_ray	ray;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	float	fov_scale;
	float	pixel_x;
	float	pixel_y;

	forward = vec3_normalize(vars->scene.camera->direction);
	right = vec3_normalize(vec3_cross(forward, vars->scene.camera->up));
	up = vec3_cross(right, forward);
	fov_scale = tanf(vars->scene.camera->field_of_view * 0.5f * M_PI / 180.0f);
	pixel_x = (2.0f * ((i + 0.5f) / vars->width) - 1.0f) * fov_scale
		* vars->aspect_ratio;
	pixel_y = (1.0f - 2.0f * ((j + 0.5f) / vars->height)) * fov_scale;
	ray.origin = vars->scene.camera->position;
	ray.direction = vec3_normalize(vec3_sum(forward,
				vec3_sum(vec3_multiply(right, pixel_x), vec3_multiply(up,
						pixel_y))));
	return (ray);
}

static bool	solve_equation(t_ray ray, t_sphere *sphere, float *t0, float *t1)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_substract(ray.origin, sphere->center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0f * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (false);
	}
	*t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
	*t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
	return (true);
}

bool	intersect_sphere(t_ray ray, t_sphere *sphere, float *t,
		t_point3 *hit_point, t_point3 *hit_normal)
{
	float	t0;
	float	t1;

	if (!solve_equation(ray, sphere, &t0, &t1))
	{
		return (false);
	}
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
	*hit_point = vec3_sum(ray.origin, vec3_multiply(ray.direction, *t));
	*hit_normal = vec3_normalize(vec3_substract(*hit_point, sphere->center));
	return (true);
}

static t_color3	calculate_lighting_sphere(t_vars *vars, t_hit_info * t_point3 hit_point,
		t_point3 hit_normal, t_material material, t_ray view_ray)
{
	t_color3	color;
	t_light		light;
	t_vec3		light_dir;
	float		light_distance;
	t_ray		shadow_ray;
	float		diffuse_factor;
	t_vec3		reflection_dir;
	t_vec3		view_dir;
	float		specular_factor;
	float		attenuation;
	t_color3	diffuse;
	t_color3	specular;

	color = color_scale(vars->scene.amb_light->color, 0.1f);
	light = *(vars->scene.light);
	light_dir = vec3_substract(light.position, hit_point);
	light_distance = vec3_length(light_dir);
	light_dir = vec3_normalize(light_dir);
	shadow_ray.origin = hit_point;
	shadow_ray.direction = light_dir;
	if (!is_in_shadow(shadow_ray, vars->elements, light_distance))
	{
		diffuse_factor = fmaxf(0.0f, vec3_dot(hit_normal, light_dir));
		reflection_dir = vec3_substract(vec3_multiply(hit_normal, 2.0f
					* vec3_dot(hit_normal, light_dir)), light_dir);
		view_dir = vec3_normalize(vec3_multiply(view_ray.direction, -1.0f));
		specular_factor = powf(fmaxf(0.0f, vec3_dot(view_dir, reflection_dir)),
				20.0f);
		attenuation = light.brightness / (light_distance * light_distance);
		diffuse = color_scale(color_multiply(light.color, material.color),
				diffuse_factor * attenuation);
		specular = color_scale(light.color, specular_factor * attenuation
				* 0.5f);
		color = color_sum(color, color_sum(diffuse, specular));
	}
	return (color);
}

void	raytrace_sphere(t_vars *vars, t_sphere *sphere)
{
	t_ray		p_ray;
	float		min_dist;
	t_point3	hit_point;
	t_point3	hit_normal;
	t_material	hit_material;
	t_hit_info	hit_info;
	float		t;
	t_point3	p_hit;
	t_point3	n_hit;
	int			i;
	int			j;

	j = 0;
	while (j < vars->height)
	{
		i = 0;
		while (i < vars->width)
		{
			p_ray = primary_ray(vars, i, j);
			min_dist = INFINITY;
			if (intersect_sphere(p_ray, sphere, &t, &p_hit, &n_hit))
			{
				if (t > EPSILON && t < vars->framebuffer[j * vars->width
					+ i].dist)
				{
					hit_info.point = p_hit;
					hit_material = sphere->material;
					if (vec3_dot(p_ray.direction, n_hit) > 0)
					{
						hit_info.normal = vec3_multiply(n_hit, -1.0f);
					}
					else
					{
						hit_info.normal = n_hit;
					}
					vars->framebuffer[j * vars->width
						+ i].color3 = calculate_lighting_sphere(vars, hit_point,
							hit_normal, hit_material, p_ray);
					vars->framebuffer[j * vars->width + i].dist = t;
				}
			}
			i++;
		}
		j++;
	}
}
