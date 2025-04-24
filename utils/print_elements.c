/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:29:57 by psenko            #+#    #+#             */
/*   Updated: 2025/04/24 17:04:19 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
//Forbidden function
//This file should be deleted
#include <stdio.h>

static void	print_colors(t_color3 *colors)
{
	printf("R: %f  G: %f  B: %f\n", colors->x, colors->y, colors->z);
}

static void	print_point(t_point3 *point)
{
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
	print_point(&(element->position));
	printf("Orient vector: ");
	print_point(&(element->direction));
	printf("Horizont field degree: %f\n", element->field_of_view);
}

static void	print_light(t_light *element)
{
	printf("Light point: ");
	print_point(&(element->position));
	printf("Light brightness: %f\n", element->brightness);
}

static void	print_sphere(t_sphere *element)
{
	printf("Sphere coord center: ");
	print_point(&(element->center));
	printf("Radius: %f\n", element->radius);
	printf("Sphere colors: ");
	print_colors(&(element->material.color));
}

static void	print_plane(t_plane *element)
{
	printf("Plane coord point: ");
	print_point(&(element->coord_point));
	printf("Normal vector: ");
	print_point(&(element->normal_vector));
	printf("Plane colors: ");
	print_colors(&(element->material.color));
}

static void	print_cylinder(t_cylinder *element)
{
	printf("Cylinder coord center: ");
	print_point(&(element->coord_center));
	printf("Normal vector axis cyl: ");
	print_point(&(element->norm_vec_axis_cyl));
	printf("Diameter: %f\n", element->diameter);
	printf("Height: %f\n", element->height);
	printf("Cylinder colors: ");
	print_colors(&(element->material.color));
}

static void	print_element(t_element *element)
{
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
