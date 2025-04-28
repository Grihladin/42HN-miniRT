/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_body.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:05:59 by mratke            #+#    #+#             */
/*   Updated: 2025/04/28 20:51:27 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static bool	cylinder_equation(t_ray ray, t_cylinder *cylinder, float *t0,
		float *t1)
{
	float		radius;
	t_vec3		axis;
	t_vec3		ray_dir_prep;
	t_vec3		oc_prep;
	t_params	p;

	axis = cylinder->norm_vec_axis_cyl;
	radius = cylinder->diameter / 2.0f;
	p.oc = vec3_substract(ray.origin, cylinder->coord_center);
	ray_dir_prep = vec3_substract(ray.direction, vec3_multiply(axis,
				vec3_dot(ray.direction, axis)));
	oc_prep = vec3_substract(p.oc, vec3_multiply(axis, vec3_dot(p.oc, axis)));
	p.a = vec3_dot(ray_dir_prep, ray_dir_prep);
	p.b = 2.0f * vec3_dot(oc_prep, ray_dir_prep);
	p.c = vec3_dot(oc_prep, oc_prep) - radius * radius;
	if (fabsf(p.a) < 0.001f)
		return (false);
	p.discriminant = p.b * p.b - 4.0f * p.a * p.c;
	if (p.discriminant < 0)
		return (false);
	*t0 = (-p.b - sqrt(p.discriminant)) / (2.0f * p.a);
	*t1 = (-p.b + sqrt(p.discriminant)) / (2.0f * p.a);
	return (true);
}

static float	analyze_roots(float hit0_valid, float hit1_valid, float t0,
		float t1)
{
	float	t_body;

	t_body = INFINITY;
	if (hit0_valid && hit1_valid)
		t_body = fminf(t0, t1);
	else if (hit0_valid)
		t_body = t0;
	else if (hit1_valid)
		t_body = t1;
	return (t_body);
}

static float	calculate_body_distance(t_cylinder *cylinder, t_ray ray,
		float t0, float t1)
{
	float		t_body;
	t_point3	p0;
	t_point3	p1;
	bool		hit0_valid;
	bool		hit1_valid;

	hit0_valid = false;
	hit1_valid = false;
	if (t0 > 0.001f)
	{
		p0 = vec3_sum(ray.origin, vec3_multiply(ray.direction, t0));
		if (is_in_bounds(cylinder, p0))
			hit0_valid = true;
	}
	if (t1 > 0.001f)
	{
		p1 = vec3_sum(ray.origin, vec3_multiply(ray.direction, t1));
		if (is_in_bounds(cylinder, p1))
			hit1_valid = true;
	}
	t_body = analyze_roots(hit0_valid, hit1_valid, t0, t1);
	return (t_body);
}

static t_hit_info	calculate_body_vector(t_hit_info hit_info, float t_body,
		t_ray ray, t_cylinder *cylinder)
{
	t_vec3		vec_to_hit;
	float		projection;
	t_point3	axis_point;

	hit_info.hit = true;
	hit_info.t = t_body;
	hit_info.point = vec3_sum(ray.origin, vec3_multiply(ray.direction, t_body));
	vec_to_hit = vec3_substract(hit_info.point, cylinder->coord_center);
	projection = vec3_dot(vec_to_hit, cylinder->norm_vec_axis_cyl);
	axis_point = vec3_sum(cylinder->coord_center,
			vec3_multiply(cylinder->norm_vec_axis_cyl, projection));
	hit_info.normal = vec3_normalize(vec3_substract(hit_info.point,
				axis_point));
	return (hit_info);
}

t_hit_info	intersect_cylinder_body(t_ray ray, t_cylinder *cylinder)
{
	t_hit_info	hit_info;
	float		t0;
	float		t1;
	float		t_body;

	hit_info.hit = false;
	hit_info.t = INFINITY;
	if (!cylinder_equation(ray, cylinder, &t0, &t1))
	{
		return (hit_info);
	}
	t_body = calculate_body_distance(cylinder, ray, t0, t1);
	if (t_body < INFINITY)
	{
		hit_info = calculate_body_vector(hit_info, t_body, ray, cylinder);
	}
	return (hit_info);
}
