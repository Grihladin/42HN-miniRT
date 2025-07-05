/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:39:49 by mratke            #+#    #+#             */
/*   Updated: 2025/07/06 01:15:16 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static t_color3	color_calculation(t_vars *vars, t_hit_info hit,
		t_material material, t_color3 color, t_vec3 light_dir,
		float light_distance, t_ray view_ray)
{
	float		diffuse_factor;
	float		specular_factor;
	float		attenuation;
	float		dot_normal_light;
	t_vec3		reflection_dir;
	t_vec3		view_dir;
	t_color3	diffuse;
	t_color3	specular;
	t_ray		shadow_ray;

	shadow_ray.origin = hit.point;
	shadow_ray.dir = light_dir;
	if (is_in_shadow(shadow_ray, vars->elements, light_distance))
		return (color);
	dot_normal_light = vec3_dot(hit.normal, light_dir);
	diffuse_factor = fmaxf(0.0f, dot_normal_light);
	if (diffuse_factor > 0.0f)
	{
		attenuation = vars->scene.light->brightness / (light_distance * light_distance);
		reflection_dir = vec3_substract(vec3_multiply(hit.normal, 
					2.0f * dot_normal_light), light_dir);
		view_dir = vec3_norm(vec3_multiply(view_ray.dir, -1.0f));
		float spec_dot = fmaxf(0.0f, vec3_dot(view_dir, reflection_dir));
		specular_factor = spec_dot * spec_dot * spec_dot * spec_dot * spec_dot;
		diffuse = color_scale(color_multiply(vars->scene.light->color,
					material.color), diffuse_factor * attenuation);
		specular = color_scale(vars->scene.light->color,
				specular_factor * attenuation * 0.5f);
		color = color_sum(color, color_sum(diffuse, specular));
	}
	return (color);
}

t_color3	calculate_lighting(t_vars *vars, t_hit_info hit,
		t_material material, t_ray view_ray)
{
	t_color3	color;
	t_vec3		light_dir;
	float		light_distance;
	color = color_scale(vars->scene.amb_light->color, 0.1f);
	light_dir = vec3_substract(vars->scene.light->position, hit.point);
	light_distance = vec3_length(light_dir);
	light_dir = vec3_norm(light_dir);
	color = color_calculation(vars, hit, material, color, light_dir,
			light_distance, view_ray);
	return (color);
}
