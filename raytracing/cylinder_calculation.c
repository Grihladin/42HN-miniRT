/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:13:52 by mratke            #+#    #+#             */
/*   Updated: 2025/04/24 16:35:02 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static bool	is_in_bounds(t_cylinder *cylinder, t_point3 hit_point)
{
	float	projection;
	t_vec3	vec_to_hit;

	vec_to_hit = vec3_substract(hit_point, cylinder->coord_center);
	projection = vec3_dot(vec_to_hit, cylinder->norm_vec_axis_cyl);
	return (projection >= -cylinder->height / 2.0f
		&& projection <= cylinder->height / 2.0f);
}

static bool	intersect_plane_cyl(t_ray ray, t_point3 plane_point,
		t_vec3 plane_normal, float *t)
{
	float	denom;

	denom = vec3_dot(ray.direction, plane_normal);
	if (fabsf(denom) < 0.001f)
	{
		return (false);
	}
	*t = vec3_dot(vec3_substract(plane_point, ray.origin), plane_normal)
		/ denom;
	if (*t < 0.001f)
	{
		return (false);
	}
	return (true);
}

static t_hit_info	intersect_cylinder_body(t_ray ray, t_cylinder *cylinder)
{
	t_hit_info	hit_info;
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
	float		t_body;
	t_vec3		vec_to_hit;
	float		projection;
	t_point3	axis_point;

	t_body = INFINITY;
	hit_info.hit = false;
	hit_info.t = INFINITY;
	hit0_valid = false;
	hit1_valid = false;
	axis = cylinder->norm_vec_axis_cyl;
	radius = cylinder->diameter / 2.0f;
	oc = vec3_substract(ray.origin, cylinder->coord_center);
	ray_dir_prep = vec3_substract(ray.direction, vec3_multiply(axis,
				vec3_dot(ray.direction, axis)));
	oc_prep = vec3_substract(oc, vec3_multiply(axis, vec3_dot(oc, axis)));
	a = vec3_dot(ray_dir_prep, ray_dir_prep);
	b = 2.0f * vec3_dot(oc_prep, ray_dir_prep);
	c = vec3_dot(oc_prep, oc_prep) - radius * radius;
	if (fabsf(a) < 0.001f)
	{
		return (hit_info);
	}
	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0)
	{
		return (hit_info);
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
		t_body = fminf(t0, t1);
	}
	else if (hit0_valid)
	{
		t_body = t0;
	}
	else if (hit1_valid)
	{
		t_body = t1;
	}
	if (t_body < INFINITY)
	{
		hit_info.hit = true;
		hit_info.t = t_body;
		hit_info.point = vec3_sum(ray.origin, vec3_multiply(ray.direction,
					t_body));
		vec_to_hit = vec3_substract(hit_info.point, cylinder->coord_center);
		projection = vec3_dot(vec_to_hit, axis);
		axis_point = vec3_sum(cylinder->coord_center, vec3_multiply(axis,
					projection));
		hit_info.normal = vec3_normalize(vec3_substract(hit_info.point,
					axis_point));
	}
	return (hit_info);
}

static t_hit_info	intersect_cylinder_cap(t_ray ray, t_cylinder *cylinder,
		bool is_top_cap)
{
	t_hit_info	hit_info;
	t_vec3		axis;
	float		half_h;
	float		radius;
	t_point3	cap_center;
	t_vec3		cap_normal;
	float		t_cap;
	t_point3	hit_point_cap;
	t_vec3		vec_to_hit;

	axis = cylinder->norm_vec_axis_cyl;
	half_h = cylinder->height / 2.0f;
	radius = cylinder->diameter / 2.0f;
	hit_info.hit = false;
	hit_info.t = INFINITY;
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
	if (intersect_plane_cyl(ray, cap_center, cap_normal, &t_cap))
	{
		hit_point_cap = vec3_sum(ray.origin, vec3_multiply(ray.direction,
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

bool	intersect_cylinder(t_ray ray, t_cylinder *cylinder, float *t,
		t_point3 *hit_point, t_point3 *hit_normal)
{
	t_hit_info	closest_hit;
	t_hit_info	body_hit;
	t_hit_info	top_cap_hit;
	t_hit_info	bottom_cap_hit;

	closest_hit.hit = false;
	closest_hit.t = INFINITY;
	body_hit = intersect_cylinder_body(ray, cylinder);
	if (body_hit.hit && body_hit.t < closest_hit.t)
	{
		closest_hit = body_hit;
	}
	top_cap_hit = intersect_cylinder_cap(ray, cylinder, true);
	if (top_cap_hit.hit && top_cap_hit.t < closest_hit.t)
	{
		closest_hit = top_cap_hit;
	}
	bottom_cap_hit = intersect_cylinder_cap(ray, cylinder, false);
	if (bottom_cap_hit.hit && bottom_cap_hit.t < closest_hit.t)
	{
		closest_hit = bottom_cap_hit;
	}
	if (closest_hit.hit)
	{
		*t = closest_hit.t;
		*hit_point = closest_hit.point;
		*hit_normal = closest_hit.normal;
		return (true);
	}
	return (false);
}

static t_color3	calculate_lighting_cylinder(t_vars *vars, t_point3 hit_point,
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

void	raytrace_cylinder(t_vars *vars, t_cylinder *cylinder)
{
	t_ray		p_ray;
	float		min_dist;
	t_point3	hit_point;
	t_point3	hit_normal;
	t_material	hit_material;
	float		t;
	t_point3	p_hit;
	t_point3	n_hit;
	int			i;
	int			j;

	cylinder->norm_vec_axis_cyl = vec3_normalize(cylinder->norm_vec_axis_cyl);
	i = 0;
	j = 0;
	while (j < vars->height)
	{
		i = 0;
		while (i < vars->width)
		{
			p_ray = primary_ray(vars, i, j);
			min_dist = INFINITY;
			if (intersect_cylinder(p_ray, cylinder, &t, &p_hit, &n_hit))
			{
				if (t > EPSILON && t < vars->frmbuf[j * vars->width
					+ i].dist)
				{
					hit_point = p_hit;
					hit_material = cylinder->material;
					if (vec3_dot(p_ray.direction, n_hit) > 0)
					{
						hit_normal = vec3_multiply(n_hit, -1.0f);
					}
					else
					{
						hit_normal = n_hit;
					}
					vars->frmbuf[j * vars->width
						+ i].color3 = calculate_lighting_cylinder(vars,
							hit_point, hit_normal, hit_material, p_ray);
					vars->frmbuf[j * vars->width + i].dist = t;
				}
			}
			i++;
		}
		j++;
	}
}
