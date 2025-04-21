/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:13:52 by mratke            #+#    #+#             */
/*   Updated: 2025/04/21 15:00:22 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	is_in_bounds(t_cylinder *cylinder, t_point3 hit_point)
{
	float	projection;
	t_vec3	vec_to_hit;

	vec_to_hit = vec3_substract(hit_point, cylinder->coord_center);
	projection = vec3_dot(vec_to_hit, cylinder->norm_vec_axis_cyl);
	return (projection >= -cylinder->height / 2.0f
		&& projection <= cylinder->height / 2.0f);
}

static bool	intersect_cylinder(t_ray ray, t_cylinder *cylinder, float *t,
		t_point3 *hit_point, t_point3 *hit_normal)
{
	t_vec3		oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t0;
	float		t1;
	t_vec3		axis;
	float		radius;
	t_vec3		ray_dir_prep;
	t_vec3		oc_prep;
	t_point3	p0;
	t_point3	p1;
	bool		hit0_valid;
	bool		hit1_valid;
	t_vec3		vec_to_hit;
	float		projection;
	t_point3	point_on_axis;

	hit0_valid = false;
	hit1_valid = false;
	oc = vec3_substract(ray.origin, cylinder->coord_center);
	axis = cylinder->norm_vec_axis_cyl;
	radius = cylinder->diameter / 2.0f;
	ray_dir_prep = vec3_substract(ray.direction, vec3_multiply(axis,
				vec3_dot(ray.direction, axis)));
	oc_prep = vec3_substract(oc, vec3_multiply(axis, vec3_dot(oc, axis)));
	a = vec3_dot(ray_dir_prep, ray_dir_prep);
	b = 2.0f * vec3_dot(oc_prep, ray_dir_prep);
	c = vec3_dot(oc_prep, oc_prep) - radius * radius;
	if (fabsf(a) < 0.0001f)
	{
		return (false);
	}
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (false);
	}
	t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
	t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (t0 > 0.001f)
	{
		p0 = vec3_sum(ray.origin, vec3_multiply(ray.direction, t0));
		if (is_in_bounds(cylinder, p0))
		{
			hit0_valid = true;
		}
	}
	if (t1 > 0.001f)
	{
		p1 = vec3_sum(ray.origin, vec3_multiply(ray.direction, t1));
		if (is_in_bounds(cylinder, p1))
		{
			hit1_valid = true;
		}
	}
	if (hit0_valid && hit1_valid)
	{
		if (t0 < t1)
		{
			*t = t0;
		}
		else
		{
			*t = t1;
		}
	}
	else if (hit0_valid)
	{
		*t = t0;
	}
	else if (hit1_valid)
	{
		*t = t1;
	}
	else
	{
		return (false);
	}
	*hit_point = vec3_sum(ray.origin, vec3_multiply(ray.direction, *t));
	vec_to_hit = vec3_substract(*hit_point, cylinder->coord_center);
	projection = vec3_dot(vec_to_hit, axis);
	point_on_axis = vec3_sum(cylinder->coord_center, vec3_multiply(axis,
				projection));
	*hit_normal = vec3_normalize(vec3_substract(*hit_point, point_on_axis));
	return (true);
}

static bool	is_in_shadow_cylinder(t_ray shadow_ray, t_cylinder *cylinder,
		float max_t)
{
	float		t;
	t_point3	hit_point;
	t_point3	hit_normal;

	if (intersect_cylinder(shadow_ray, cylinder, &t, &hit_point, &hit_normal))
	{
		if (t < max_t)
		{
			return (true);
		}
	}
	return (false);
}

static t_color3	calculate_lighting(t_vars *vars, t_cylinder *cylinder,
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
	if (!is_in_shadow_cylinder(shadow_ray, cylinder, light_distance))
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

void	raytrace_cylinder(t_vars *vars, t_cylinder *cylinder)
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

	i = 0;
	j = 0;
	while (j < vars->height)
	{
		while (i < vars->width)
		{
			p_ray = primary_ray(vars, i, j);
			min_dist = INFINITY;
			found_intersection = false;
			if (intersect_cylinder(p_ray, cylinder, &t, &p_hit, &n_hit))
			{
				if (t < min_dist)
				{
					min_dist = t;
					hit_point = p_hit;
					hit_normal = n_hit;
					hit_material = cylinder->material;
					found_intersection = true;
				}
			}
			if (found_intersection)
			{
				vars->framebuffer[j * vars->width
					+ i] = calculate_lighting(vars, cylinder, hit_point,
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
