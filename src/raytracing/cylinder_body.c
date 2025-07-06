/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_body.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:05:59 by mratke            #+#    #+#             */
/*   Updated: 2025/07/06 01:12:49 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	cylinder_equation(t_ray ray, t_cylinder *cylinder, float *t0,
		float *t1)
{
	float		radius;
	t_vec3		axis;
	t_vec3		ray_dir_prep;
	t_vec3		oc_prep;
	t_vec3		oc;
	float		a, b, c;
	float		discriminant;
	float		sqrt_discriminant;
	float		dot_ray_axis;
	float		dot_oc_axis;

	axis = cylinder->norm_vec_axis_cyl;
	radius = cylinder->diameter * 0.5f;
	oc = vec3_substract(ray.origin, cylinder->coord_center);
	dot_ray_axis = vec3_dot(ray.dir, axis);
	dot_oc_axis = vec3_dot(oc, axis);
	ray_dir_prep = vec3_substract(ray.dir, vec3_multiply(axis, dot_ray_axis));
	oc_prep = vec3_substract(oc, vec3_multiply(axis, dot_oc_axis));
	a = vec3_dot(ray_dir_prep, ray_dir_prep);
	if (a < EPSILON)
		return (false);
	b = 2.0f * vec3_dot(oc_prep, ray_dir_prep);
	c = vec3_dot(oc_prep, oc_prep) - radius * radius;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return (false);
	sqrt_discriminant = sqrtf(discriminant);
	*t0 = (-b - sqrt_discriminant) / (2.0f * a);
	*t1 = (-b + sqrt_discriminant) / (2.0f * a);
	return (true);
}


static float	calculate_body_distance(t_cylinder *cylinder, t_ray ray,
		float t0, float t1)
{
	t_point3	p0, p1;
	bool		hit0_valid = false;
	bool		hit1_valid = false;
	
	if (t0 > EPSILON)
	{
		p0 = vec3_sum(ray.origin, vec3_multiply(ray.dir, t0));
		hit0_valid = is_in_bounds(cylinder, p0);
	}
	if (t1 > EPSILON)
	{
		p1 = vec3_sum(ray.origin, vec3_multiply(ray.dir, t1));
		hit1_valid = is_in_bounds(cylinder, p1);
	}

	if (hit0_valid && hit1_valid)
		return (fminf(t0, t1));
	else if (hit0_valid)
		return (t0);
	else if (hit1_valid)
		return (t1);
	
	return (INFINITY);
}

static t_hit_info	calculate_body_vector(t_hit_info hit_info, float t_body,
		t_ray ray, t_cylinder *cylinder)
{
	t_vec3		vec_to_hit;
	float		projection;
	t_point3	axis_point;

	hit_info.hit = true;
	hit_info.t = t_body;
	hit_info.point = vec3_sum(ray.origin, vec3_multiply(ray.dir, t_body));
	vec_to_hit = vec3_substract(hit_info.point, cylinder->coord_center);
	projection = vec3_dot(vec_to_hit, cylinder->norm_vec_axis_cyl);
	axis_point = vec3_sum(cylinder->coord_center,
			vec3_multiply(cylinder->norm_vec_axis_cyl, projection));
	hit_info.normal = vec3_norm(vec3_substract(hit_info.point,
				axis_point));
	return (hit_info);
}

t_hit_info	intersect_cylinder_body(t_ray ray, t_cylinder *cylinder)
{
	t_hit_info	hit_info;
	float		t0, t1;
	float		t_body;

	hit_info.hit = false;
	hit_info.t = INFINITY;
	
	if (!cylinder_equation(ray, cylinder, &t0, &t1))
		return (hit_info);
	
	t_body = calculate_body_distance(cylinder, ray, t0, t1);
	if (t_body < INFINITY)
		hit_info = calculate_body_vector(hit_info, t_body, ray, cylinder);
	
	return (hit_info);
}
