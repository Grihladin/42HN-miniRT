/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:23:12 by mratke            #+#    #+#             */
/*   Updated: 2025/04/16 20:27:44 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	primary_ray(t_vars *vars, int i, int j)
{
	t_ray	ray;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	float	fov_scale;
	float	pixel_x;
	float	pixel_y;

	forward = vec3_normalize(vars->camera->direction);
	right = vec3_normalize(vec3_cross(forward, vars->camera->up));
	up = vec3_cross(right, forward);
	fov_scale = tanf(vars->camera->fov * 0.5f * M_PI / 180.0f);
	pixel_x = (2.0f * ((i + 0.5f) / vars->width) - 1.0f) * fov_scale
		* vars->camera->aspect_ratio;
	pixel_y = (1.0f - 2.0f * ((j + 0.5f) / vars->height)) * fov_scale;
	ray.origin = vars->camera->position;
	ray.direction = vec3_normalize(vec3_sum(forward,
				vec3_sum(vec3_multiply(right, pixel_x), vec3_multiply(up,
						pixel_y))));
	return (ray);
}

bool	intersect_sphere(t_ray ray, t_sphere *sphere, float *t,
		t_point3 *hit_point, t_point3 *hit_normal)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t0;
	float	t1;

	oc = vec3_subtract(ray.origin, sphere->center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0f * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (false);
	}
	t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
	t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (t0 > 0.001f)
	{
		*t = t0;
	}
	else if (t1 > 0.001f)
	{
		*t = t1;
	}
	else
	{
		return (false);
	}
	*hit_point = vec3_sum(ray.origin, vec3_multiply(ray.direction, *t));
	*hit_normal = vec3_normalize(vec3_subtract(*hit_point, sphere->center));
	return (true);
}

bool	is_in_shadow(t_ray shadow_ray, t_scene scene, float max_t)
{
	float		t;
	t_point3	hit_point;
	t_point3	hit_normal;

	if (intersect_sphere(shadow_ray, scene.sphere, &t, &hit_point, &hit_normal))
	{
		if (t < max_t)
		{
			return (true);
		}
	}
	return (false);
}

t_color3	calculate_lighting(t_scene scene, t_point3 hit_point,
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

	color = color_scale(scene.ambient_light, 0.1f);
	light = *scene.light;
	light_dir = vec3_subtract(light.position, hit_point);
	light_distance = vec3_length(light_dir);
	light_dir = vec3_normalize(light_dir);
	shadow_ray.origin = hit_point;
	shadow_ray.direction = light_dir;
	if (!is_in_shadow(shadow_ray, scene, light_distance))
	{
		diffuse_factor = fmaxf(0.0f, vec3_dot(hit_normal, light_dir));
		reflection_dir = vec3_subtract(vec3_multiply(hit_normal, 2.0f
					* vec3_dot(hit_normal, light_dir)), light_dir);
		view_dir = vec3_normalize(vec3_multiply(view_ray.direction, -1.0f));
		specular_factor = powf(fmaxf(0.0f, vec3_dot(view_dir, reflection_dir)),
				20.0f);
		attenuation = light.intensity / (light_distance * light_distance);
		diffuse = color_scale(color_multiply(light.color, material.color),
				diffuse_factor * attenuation);
		specular = color_scale(light.color, specular_factor * attenuation
				* 0.5f);
		color = color_sum(color, color_sum(diffuse, specular));
	}
	return (color);
}

void	raytrace(t_vars *vars, t_scene scene, t_color3 *framebuffer)
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

	// Loop over each pixel in the image
	for (int j = 0; j < vars->height; j++)
	{
		for (int i = 0; i < vars->width; i++)
		{
			// Compute primary ray for this pixel
			p_ray = primary_ray(vars, i, j);
			// Initialize closest intersection
			min_dist = INFINITY;
			found_intersection = false;
			if (intersect_sphere(p_ray, vars->scene.sphere, &t, &p_hit, &n_hit))
			{
				if (t < min_dist)
				{
					min_dist = t;
					hit_point = p_hit;
					hit_normal = n_hit;
					hit_material = vars->scene.sphere->material;
					found_intersection = true;
				}
			}
			if (found_intersection)
			{
				framebuffer[j * vars->width + i] = calculate_lighting(scene,
						hit_point, hit_normal, hit_material, p_ray);
			}
			else
			{
				framebuffer[j * vars->width + i] = vec3_create(0.0f, 0.0f,
						0.0f);
			}
		}
	}
}

void	save_image(t_vars *vars, t_color3 *framebuffer)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	// Write pixel data
	for (int j = 0; j < vars->height; j++)
	{
		for (int i = 0; i < vars->width; i++)
		{
			// Convert floating-point color to byte
			r = (unsigned char)(255.0f * fminf(1.0f, fmaxf(0.0f, framebuffer[j
							* vars->width + i].x)));
			g = (unsigned char)(255.0f * fminf(1.0f, fmaxf(0.0f, framebuffer[j
							* vars->width + i].y)));
			b = (unsigned char)(255.0f * fminf(1.0f, fmaxf(0.0f, framebuffer[j
							* vars->width + i].z)));
			mlx_put_pixel(vars->image, i, j,
				(uint32_t)(r << 16) | (g << 8) | b);
		}
	}
	vars->need_redraw = 1;
}
