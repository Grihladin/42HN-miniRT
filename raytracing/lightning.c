/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:39:49 by mratke            #+#    #+#             */
/*   Updated: 2025/04/29 19:26:35 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static t_color3	color_calculation(t_vars *vars, t_lightning_calc l_v,
		t_material material, t_color3 color)
{
	if (!is_in_shadow(l_v.shadow_ray, vars->elements,
			l_v.light_distance))
	{
		l_v.diffuse_factor = fmaxf(0.0f, vec3_dot(l_v.hit.normal,
					l_v.light_dir));
		l_v.reflection_dir = vec3_substract(vec3_multiply(l_v.hit.normal,
					2.0f * vec3_dot(l_v.hit.normal,
						l_v.light_dir)), l_v.light_dir);
		l_v.view_dir = vec3_norm(vec3_multiply(l_v.view_ray.dir, -1.0f));
		l_v.specular_factor = powf(fmaxf(0.0f,
					vec3_dot(l_v.view_dir, l_v.reflection_dir)),
				20.0f);
		l_v.attenuation = l_v.light.brightness
			/ (l_v.light_distance * l_v.light_distance);
		l_v.diffuse = color_scale(color_multiply(l_v.light.color,
					material.color), l_v.diffuse_factor
				* l_v.attenuation);
		l_v.specular = color_scale(l_v.light.color,
				l_v.specular_factor * l_v.attenuation * 0.5f);
		color = color_sum(color, color_sum(l_v.diffuse,
					l_v.specular));
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
	light_vars.light_dir = vec3_norm(light_vars.light_dir);
	light_vars.shadow_ray.origin = hit.point;
	light_vars.shadow_ray.dir = light_vars.light_dir;
	color = color_calculation(vars, light_vars, material, color);
	return (color);
}
