/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:56:23 by psenko            #+#    #+#             */
/*   Updated: 2025/04/18 11:29:03 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	out_image(t_vars *vars)
{
	int				j;
	int				i;
	t_color_int		color;

	color.intgr = 0;
	color.bytes[0] = 0xFF;
	j = 0;
	while (j < vars->height)
	{
		i = 0;
		while (i < vars->width)
		{
			color.bytes[3] = (unsigned char)(255.0f * fminf(1.0f,
						fmaxf(0.0f, vars->framebuffer[j * vars->width + i].x)));
			color.bytes[2] = (unsigned char)(255.0f * fminf(1.0f,
						fmaxf(0.0f, vars->framebuffer[j * vars->width + i].y)));
			color.bytes[1] = (unsigned char)(255.0f * fminf(1.0f,
						fmaxf(0.0f, vars->framebuffer[j * vars->width + i].z)));
			mlx_put_pixel(vars->image, i, j, color.intgr);
			i++;
		}
		j++;
	}
}

int	redraw_image(t_vars *vars)
{
	t_element	*element;
	t_list		*elements;
	t_sphere	*sphere;
	t_cylinder	*cylinder;

	elements = vars->elements;
	ft_printf("Redraw\n");
	while (elements != NULL)
	{
		element = elements->content;
		if (element->type == SPHERE)
		{
			sphere = element->params;
			raytrace_sphere(vars, sphere);
		}
		else if (element->type == CYLINDER)
		{
			cylinder = element->params;
			raytrace_cylinder(vars, element->params);
		}
		elements = elements->next;
	}
	out_image(vars);
	return (1);
}
