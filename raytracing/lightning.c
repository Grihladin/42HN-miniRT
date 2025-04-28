/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:39:49 by mratke            #+#    #+#             */
/*   Updated: 2025/04/28 20:56:58 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static t_color3	color_calculation(t_vars *vars, t_lightning_calc light_vars,
		t_material material, t_color3 color)
{
	if (!is_in_shadow(light_vars.shadow_ray, vars->elements,
			light_vars.light_distance))
	{
		light_vars.diffuse_factor = fmaxf(0.0f, vec3_dot(light_vars.hit.normal,
					light_vars.light_dir));
		light_vars.reflection_dir = vec3_substract(vec3_multiply(light_vars.hit.normal,
					2.0f * vec3_dot(light_vars.hit.normal,
						light_vars.light_dir)), light_vars.light_dir);
		light_vars.view_dir = vec3_normalize(vec3_multiply(light_vars.view_ray.direction,
					-1.0f));
		light_vars.specular_factor = powf(fmaxf(0.0f,
					vec3_dot(light_vars.view_dir, light_vars.reflection_dir)),
				20.0f);
		light_vars.attenuation = light_vars.light.brightness
			/ (light_vars.light_distance * light_vars.light_distance);
		light_vars.diffuse = color_scale(color_multiply(light_vars.light.color,
					material.color), light_vars.diffuse_factor
				* light_vars.attenuation);
		light_vars.specular = color_scale(light_vars.light.color,
				light_vars.specular_factor * light_vars.attenuation * 0.5f);
		color = color_sum(color, color_sum(light_vars.diffuse,
					light_vars.specular));
	}
	return (color);
}

t_color3	calculate_lighting(t_vars *vars, t_hit_info hit,
		t_material material, t_ray view_ray)
{
	t_color3			color;
	t_lightning_calc	light_vars;

	light_vars.hit = hit;
	light_vars.view_ray = view_ray;
	color = color_scale(vars->scene.amb_light->color, 0.1f);
	light_vars.light = *(vars->scene.light);
	light_vars.light_dir = vec3_substract(light_vars.light.position, hit.point);
	light_vars.light_distance = vec3_length(light_vars.light_dir);
	light_vars.light_dir = vec3_normalize(light_vars.light_dir);
	light_vars.shadow_ray.origin = hit.point;
	light_vars.shadow_ray.direction = light_vars.light_dir;
	color = color_calculation(vars, light_vars, material, color);
	return (color);
}
