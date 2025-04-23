/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:18:37 by mratke            #+#    #+#             */
/*   Updated: 2025/04/23 13:36:52 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	intersect_plane(t_ray ray, t_plane *plane, float *t,
		t_point3 *hit_point, t_point3 *hit_normal)
{
	t_vec3	p0_l0;
	float	denom;

	denom = vec3_dot(plane->normal_vector, ray.direction);
	if (fabsf(denom) < 0.001f)
	{
		return (false);
	}
	p0_l0 = vec3_substract(plane->coord_point, ray.origin);
	*t = vec3_dot(p0_l0, plane->normal_vector) / denom;
	if (*t < 0.001f)
	{
		return (false);
	}
	*hit_point = vec3_sum(ray.origin, vec3_multiply(ray.direction, *t));
	*hit_normal = plane->normal_vector;
	return (true);
}

static bool	is_in_shadow_plane(t_ray shadow_ray, t_plane *plane, float max_t)
{
	float		t;
	t_point3	hit_point;
	t_point3	hit_normal;

	if (intersect_plane(shadow_ray, plane, &t, &hit_point, &hit_normal))
	{
		if (t > 0.001f && t < max_t)
		{
			return (true);
		}
	}
	return (false);
}

static t_color3	calculate_lighting_plane(t_vars *vars, t_plane *plane,
		t_point3 hit_point, t_point3 hit_normal, t_material material,
		t_ray view_ray)
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
	if (!is_in_shadow_plane(shadow_ray, plane, light_distance))
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

void	raytrace_plane(t_vars *vars, t_plane *plane)
{
	t_ray		p_ray;
	float		min_dist;
	t_point3	hit_point;
	t_point3	hit_normal;
	t_material	hit_material;
	bool		found_intersection;
	float		t;
	t_point3	p_hit;
	t_point3	n_hit;
	int			i;
	int			j;

	plane->normal_vector = vec3_normalize(plane->normal_vector);
	i = 0;
	j = 0;
	while (j < vars->height)
	{
		i = 0;
		while (i < vars->width)
		{
			p_ray = primary_ray(vars, i, j);
			min_dist = INFINITY;
			found_intersection = false;
			if (intersect_plane(p_ray, plane, &t, &p_hit, &n_hit))
			{
				if (t < min_dist)
				{
					min_dist = t;
					hit_point = p_hit;
					hit_normal = n_hit;
					hit_material = plane->material;
					found_intersection = true;
				}
			}
			if (found_intersection)
			{
				vars->framebuffer[j * vars->width
					+ i] = calculate_lighting_plane(vars, plane, hit_point,
						hit_normal, hit_material, p_ray);
			}
			else
			{
				vars->framebuffer[j * vars->width + i] = vec3_create(0.0f, 0.0f,
						0.0f);
			}
			i++;
		}
		j++;
	}
}
