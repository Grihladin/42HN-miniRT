/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:02:25 by psenko            #+#    #+#             */
/*   Updated: 2025/04/15 20:05:20 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_color	read_colors(const char *str)
{
	char		**colors_arr;
	t_color	color;

	colors_arr = ft_split(str, ',');
	color.x = (unsigned char) ft_atoi(colors_arr[0]);
	color.y = (unsigned char) ft_atoi(colors_arr[1]);
	color.z = (unsigned char) ft_atoi(colors_arr[2]);
	free_arr_of_str(&colors_arr);
	return (color);
}

t_point	read_point(const char *str)
{
	char		**point_arr;
	t_point		point;

	point_arr = ft_split(str, ',');
	point.x = ft_atof(point_arr[0]);
	point.y = ft_atof(point_arr[1]);
	point.z = ft_atof(point_arr[2]);
	free_arr_of_str(&point_arr);
	return (point);
}

static t_ambient_lightning	*read_ambient_lightning(t_list *element_params)
{
	t_ambient_lightning		*new_amb_light;

	new_amb_light = ft_calloc(1, sizeof (t_ambient_lightning));
	if (new_amb_light == NULL)
		return (NULL);
	new_amb_light->amb_light_rate = ft_atof(element_params->content);
	element_params = element_params->next;
	new_amb_light->color = read_colors(element_params->content);
	return (new_amb_light);
}

static t_camera	*read_camera(t_list *element_params)
{
	t_camera		*new_camera;

	new_camera = ft_calloc(1, sizeof (t_camera));
	if (new_camera == NULL)
		return (NULL);
	new_camera->view_point = read_point(element_params->content);
	element_params = element_params->next;
	new_camera->orient_vector = read_point(element_params->content);
	element_params = element_params->next;
	new_camera->horizont_field_degree = (unsigned char)
		ft_atoi(element_params->content);
	new_camera->up = vec3_create(0, 1, 0);
	return (new_camera);
}

int	read_element(t_vars *vars, t_list *element_params)
{
	t_element		*new_element;
	t_list			*new_el;

	new_element = ft_calloc(1, sizeof (t_element));
	if (ft_strcmp(element_params->content, "A") == 0)
	{
		new_element->type = AMBIENT_LIGHTNING;
		new_element->params = read_ambient_lightning(element_params->next);
	}
	else if (ft_strcmp(element_params->content, "C") == 0)
	{
		new_element->type = CAMERA;
		new_element->params = read_camera(element_params->next);
	}
	else if (ft_strcmp(element_params->content, "L") == 0)
	{
		new_element->type = LIGHT;
		new_element->params = read_light(element_params->next);
	}
	else if (ft_strcmp(element_params->content, "sp") == 0)
	{
		new_element->type = SPHERE;
		new_element->params = read_sphere(element_params->next);
	}
	else if (ft_strcmp(element_params->content, "pl") == 0)
	{
		new_element->type = PLANE;
		new_element->params = read_plane(element_params->next);
	}
	else if (ft_strcmp(element_params->content, "cy") == 0)
	{
		new_element->type = CYLINDER;
		new_element->params = read_cylinder(element_params->next);
	}
	if (new_element->type != 0)
	{
		if (check_unique_element(vars->elements, new_element->type))
		{
			free(new_element);
			return (print_error(element_params->content, ERROR_ELEMENT_NOT_UNIQUE), 1);
		}
		new_el = ft_calloc(sizeof (t_list), 1);
		if (new_el == NULL)
			return (1);
		new_el->content = new_element;
		ft_lstadd_back(&(vars->elements), new_el);
	}
	return (0);
}
