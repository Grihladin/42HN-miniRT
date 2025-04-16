/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:29:57 by psenko            #+#    #+#             */
/*   Updated: 2025/04/16 17:19:13 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
//Forbidden function
#include <stdio.h>

static void	print_colors(t_colorf *colors)
{
	printf("R: %f  G: %f  B: %f\n", colors->red, colors->green, colors->blue);
}

static void	print_point(t_point *point)
{
	// ft_printf("Point \\ Vector:\n");
	printf("%f  %f  %f\n", point->x, point->y, point->z);
}

static void	print_ambient_lightning(t_ambient_lightning *element)
{
	printf("Ambient light rate: %f\n", element->amb_light_rate);
	print_colors(&(element->color));
}

static void	print_camera(t_camera *element)
{
	printf("Camera view point: ");
	print_point(&(element->view_point));
	printf("Orient vector: ");
	print_point(&(element->orient_vector));
	printf("Horizont field degree: %u\n", element->horizont_field_degree);
}

static void	print_light(t_light *element)
{
	printf("Light point: ");
	print_point(&(element->light_point));
	printf("Light brightness: %f\n", element->light_brightness);
}

static void	print_sphere(t_sphere *element)
{
	printf("Sphere coord center: ");
	print_point(&(element->coord_center));
	printf("Diameter: %f\n", element->diameter);
	printf("Sphere colors: ");
	print_colors(&(element->color));
}

static void	print_plane(t_plane *element)
{
	printf("Plane coord point: ");
	print_point(&(element->coord_point));
	printf("Normal vector: ");
	print_point(&(element->normal_vector));
	printf("Plane colors: ");
	print_colors(&(element->color));
}

static void	print_cylinder(t_cylinder *element)
{
	printf("Cylinder coord center: ");
	print_point(&(element->coord_center));
	printf("Normal vector axis cyl: ");
	print_point(&(element->normal_vector_axis_cyl));
	printf("Diameter: %f\n", element->diameter);
	printf("Height: %f\n", element->height);
	printf("Cylinder colors: ");
	print_colors(&(element->color));
}

static void	print_element(t_element *element)
{
	// if (element->type == AMBIENT_LIGHTNING)
	// 	print_ambient_lightning(element->params);
	// else if (element->type == CAMERA)
	// 	print_camera(element->params);
	// else if (element->type == LIGHT)
	// 	print_light(element->params);
	if (element->type == SPHERE)
		print_sphere(element->params);
	else if (element->type == PLANE)
		print_plane(element->params);
	else if (element->type == CYLINDER)
		print_cylinder(element->params);
}

void	print_elements(t_list *elements)
{
	printf("Print Elements:\n");
	while (elements != NULL)
	{
		print_element(elements->content);
		elements = elements->next;
		printf("\n");
	}
}
void	print_scene(t_scene *scene)
{
	printf("Print Scene:\n");
	print_ambient_lightning(scene->amb_light);
	printf("\n");
	print_camera(scene->camera);
	printf("\n");
	print_light(scene->light);
	printf("\n");
}
