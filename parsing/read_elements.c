/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:02:25 by psenko            #+#    #+#             */
/*   Updated: 2025/04/18 16:36:43 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	read_colors(const char *str, t_color3 *color)
{
	char			**colors_arr;

	colors_arr = ft_split(str, ',');
	if (arr_size(colors_arr) < 3)
		return (free_arr_of_str(&colors_arr), 1);
	color->x = ((float) ft_atoi(colors_arr[0])) / 255;
	color->y = ((float) ft_atoi(colors_arr[1])) / 255;
	color->z = ((float) ft_atoi(colors_arr[2])) / 255;
	free_arr_of_str(&colors_arr);
	return (0);
}

int	read_point(const char *str, t_point3 *point)
{
	char		**point_arr;

	point_arr = ft_split(str, ',');
	if (arr_size(point_arr) < 3)
		return (free_arr_of_str(&point_arr), 1);
	point->x = ft_atof(point_arr[0]);
	point->y = ft_atof(point_arr[1]);
	point->z = ft_atof(point_arr[2]);
	free_arr_of_str(&point_arr);
	return (0);
}

static t_ambient_lightning	*read_ambient_lightning(t_list *element_params)
{
	t_ambient_lightning		*new_amb_light;

	new_amb_light = ft_calloc(1, sizeof (t_ambient_lightning));
	if (new_amb_light == NULL)
		return (print_error(NULL, ERR_ALC_MEM), NULL);
	new_amb_light->amb_light_rate = ft_atof(element_params->content);
	element_params = element_params->next;
	if (read_colors(element_params->content, &(new_amb_light->color)))
		return (free(new_amb_light), NULL);
	return (new_amb_light);
}

static t_camera	*read_camera(t_list *element_params)
{
	t_camera		*new_camera;

	new_camera = ft_calloc(1, sizeof (t_camera));
	if (new_camera == NULL)
		return (NULL);
	if (read_point(element_params->content, &(new_camera->position)))
		return (free(new_camera), NULL);
	element_params = element_params->next;
	if (read_point(element_params->content, &(new_camera->direction)))
		return (free(new_camera), NULL);
	element_params = element_params->next;
	new_camera->field_of_view = (float) ft_atoi(element_params->content);
	new_camera->up = vec3_create(0.0f, 1.0f, 0.0f);
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
	if ((new_element->type != 0) && (new_element->params != NULL))
	{
		if (check_unique_element(vars, new_element->type))
		{
			free(new_element);
			return (print_error(element_params->content,
					ERR_EL_NOT_UNIQ), 1);
		}
		if (new_element->type == AMBIENT_LIGHTNING)
		{
			vars->scene.amb_light = new_element->params;
			free(new_element);
		}
		else if (new_element->type == CAMERA)
		{
			vars->scene.camera = new_element->params;
			free(new_element);
		}
		else if (new_element->type == LIGHT)
		{
			vars->scene.light = new_element->params;
			free(new_element);
		}
		else
		{
			new_el = ft_calloc(sizeof (t_list), 1);
			if (new_el == NULL)
				return (free(new_element), 1);
			new_el->content = new_element;
			ft_lstadd_back(&(vars->elements), new_el);
		}

	}
	else if ((new_element->params == NULL) && (ft_strncmp(element_params->content, "#", 1) != 0))
	{
		print_error(NULL, ERR_CRT_EL);
		return (free(new_element), 1);
	}
	return (0);
}
