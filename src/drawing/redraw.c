/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:56:23 by psenko            #+#    #+#             */
/*   Updated: 2025/07/06 01:34:02 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	out_image(t_vars *vars)
{
	int			j;
	int			i;
	t_color_int	color;

	color.bytes[0] = 0xFF;
	j = 0;
	while (j < vars->height)
	{
		i = 0;
		while (i < vars->width)
		{
			color.bytes[3] = (unsigned char)(255.0f * fminf(1.0f, fmaxf(0.0f,
							vars->frmbuf[j * vars->width + i].color3.x)));
			color.bytes[2] = (unsigned char)(255.0f * fminf(1.0f, fmaxf(0.0f,
							vars->frmbuf[j * vars->width + i].color3.y)));
			color.bytes[1] = (unsigned char)(255.0f * fminf(1.0f, fmaxf(0.0f,
							vars->frmbuf[j * vars->width + i].color3.z)));
			mlx_put_pixel(vars->image, i, j, color.intgr);
			i++;
		}
		j++;
	}
}



static void	trace_pixel(t_vars *vars, int i, int j)
{
	t_ray		p_ray;
	t_list		*elements;
	t_element	*element;
	float		closest_t;
	t_hit_info	closest_hit;
	t_material	closest_material;
	bool		hit_found;

	p_ray = primary_ray(vars, i, j);
	closest_t = INFINITY;
	hit_found = false;
	elements = vars->elements;
	
	while (elements != NULL)
	{
		element = elements->content;
		float t;
		t_hit_info hit;
		
		if ((element->type == SPHERE && intersect_sphere(p_ray, element->params, &t, &hit)) ||
			(element->type == CYLINDER && intersect_cylinder(p_ray, element->params, &t, &hit)) ||
			(element->type == PLANE && intersect_plane(p_ray, element->params, &t, &hit)))
		{
			if (t > EPSILON && t < closest_t)
			{
				closest_t = t;
				closest_hit = hit;
				if (element->type == SPHERE)
					closest_material = ((t_sphere*)element->params)->material;
				else if (element->type == CYLINDER)
					closest_material = ((t_cylinder*)element->params)->material;
				else if (element->type == PLANE)
					closest_material = ((t_plane*)element->params)->material;
				hit_found = true;
			}
		}
		elements = elements->next;
	}
	
	if (hit_found)
	{
		if (vec3_dot(p_ray.dir, closest_hit.normal) > 0)
			closest_hit.normal = vec3_multiply(closest_hit.normal, -1.0f);
		
		vars->frmbuf[j * vars->width + i].color3 = calculate_lighting(vars, closest_hit, closest_material, p_ray);
		vars->frmbuf[j * vars->width + i].dist = closest_t;
	}
}

int	redraw_image(t_vars *vars)
{
	int	i;
	int	j;

	free_framebuffer(vars);
	
	j = 0;
	while (j < vars->height)
	{
		i = 0;
		while (i < vars->width)
		{
			trace_pixel(vars, i, j);
			i++;
		}
		j++;
	}
	out_image(vars);
	return (1);
}
