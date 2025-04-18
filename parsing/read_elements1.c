/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:19:10 by psenko            #+#    #+#             */
/*   Updated: 2025/04/18 11:03:18 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_light	*read_light(t_list *element_params)
{
	t_light		*new_light;

	new_light = ft_calloc(1, sizeof (t_light));
	if (new_light == NULL)
		return (NULL);
	new_light->position = read_point(element_params->content);
	element_params = element_params->next;
	new_light->brightness = ft_atof(element_params->content) * 1000;
	element_params = element_params->next;
	new_light->color = read_colors(element_params->content);
	return (new_light);
}

t_sphere	*read_sphere(t_list *element_params)
{
	t_sphere		*new_sphere;

	new_sphere = ft_calloc(1, sizeof (t_sphere));
	if (new_sphere == NULL)
		return (NULL);
	new_sphere->center = read_point(element_params->content);
	element_params = element_params->next;
	new_sphere->diameter = ft_atof(element_params->content);
	element_params = element_params->next;
	new_sphere->material.color = read_colors(element_params->content);
	new_sphere->radius = new_sphere->diameter / 2;
	new_sphere->material.reflectivity = DEFAULT_REFLECTIVITY;
	return (new_sphere);
}

t_plane	*read_plane(t_list *element_params)
{
	t_plane		*new_plane;

	new_plane = ft_calloc(1, sizeof (t_plane));
	if (new_plane == NULL)
		return (NULL);
	new_plane->coord_point = read_point(element_params->content);
	element_params = element_params->next;
	new_plane->normal_vector = read_point(element_params->content);
	element_params = element_params->next;
	new_plane->material.color = read_colors(element_params->content);
	new_plane->material.reflectivity = DEFAULT_REFLECTIVITY;
	return (new_plane);
}

t_cylinder	*read_cylinder(t_list *element_params)
{
	t_cylinder		*new_cylinder;

	new_cylinder = ft_calloc(1, sizeof (t_cylinder));
	if (new_cylinder == NULL)
		return (NULL);
	new_cylinder->coord_center = read_point(element_params->content);
	element_params = element_params->next;
	new_cylinder->normal_vector_axis_cyl = read_point(element_params->content);
	element_params = element_params->next;
	new_cylinder->diameter = ft_atof(element_params->content);
	element_params = element_params->next;
	new_cylinder->height = ft_atof(element_params->content);
	element_params = element_params->next;
	new_cylinder->material.color = read_colors(element_params->content);
	new_cylinder->material.reflectivity = DEFAULT_REFLECTIVITY;
	return (new_cylinder);
}
