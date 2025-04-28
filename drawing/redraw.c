/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:56:23 by psenko            #+#    #+#             */
/*   Updated: 2025/04/28 19:57:22 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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

static void	raytrace(t_vars *vars, t_element *element)
{
	int	i;
	int	j;

	j = 0;
	while (j < vars->height)
	{
		i = 0;
		while (i < vars->width)
		{
			if (element->type == CYLINDER)
				cylinder_calculation(vars, element->params, i, j);
			else if (element->type == SPHERE)
				sphere_calculation(vars, element->params, i, j);
			else if (element->type == PLANE)
				plane_calculation(vars, element->params, i, j);
			i++;
		}
		j++;
	}
}

int	redraw_image(t_vars *vars)
{
	t_element	*element;
	t_list		*elements;

	elements = vars->elements;
	free_framebuffer(vars);
	while (elements != NULL)
	{
		element = elements->content;
		raytrace(vars, element);
		elements = elements->next;
	}
	out_image(vars);
	return (1);
}
