/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:02:25 by psenko            #+#    #+#             */
/*   Updated: 2025/07/06 02:24:16 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	validate_color_component(int val)
{
	return (val >= 0 && val <= 255);
}

int	read_colors(const char *str, t_color3 *color)
{
	char		**colors_arr;
	int			rgb[3];
	int			i;

	colors_arr = ft_split(str, ',');
	if (!colors_arr || arr_size(colors_arr) < 3)
		return (print_error(NULL, ERR_CLR), free_arr_of_str(&colors_arr), 1);
	i = -1;
	while (++i < 3)
	{
		if (!is_digits(colors_arr[i]))
			return (free_arr_of_str(&colors_arr),
				print_error(NULL, ERR_PRM_NOT_NUMB), 1);
		rgb[i] = ft_atoi(colors_arr[i]);
		if (!validate_color_component(rgb[i]))
			return (free_arr_of_str(&colors_arr), 
				print_error(NULL, ERR_CLR), 1);
	}
	color->x = rgb[0] / 255.0f;
	color->y = rgb[1] / 255.0f;
	color->z = rgb[2] / 255.0f;
	free_arr_of_str(&colors_arr);
	return (0);
}

int	read_point(const char *str, t_point3 *point)
{
	char		**point_arr;
	int			i;

	point_arr = ft_split(str, ',');
	if (!point_arr || arr_size(point_arr) < 3)
		return (print_error(NULL, ERR_CNT_PARAMS),
			free_arr_of_str(&point_arr), 1);
	i = -1;
	while (++i < 3)
		if (!is_float_digit(point_arr[i]))
			return (free_arr_of_str(&point_arr),
				print_error(NULL, ERR_PRM_NOT_NUMB), 1);
	point->x = ft_atof(point_arr[0]);
	point->y = ft_atof(point_arr[1]);
	point->z = ft_atof(point_arr[2]);
	free_arr_of_str(&point_arr);
	return (0);
}

static int	is_valid_vector_component(float val)
{
	return (val >= -1.0f && val <= 1.0f);
}

int	read_vector(const char *str, t_point3 *point)
{
	float	length;

	if (read_point(str, point) != 0)
		return (1);
	if (!is_valid_vector_component(point->x) || 
		!is_valid_vector_component(point->y) ||
		!is_valid_vector_component(point->z))
		return (print_error(NULL, ERR_VAL_NOT_IN_RANGE), 1);
	length = vec3_length(*point);
	if (length == 0.0f)
		return (print_error(NULL, ERR_VEC_NOT_NORM), 1);
	if (length < 0.999f || length > 1.001f)
	{
		ft_printf("Vector is not normalized. Normalizing...\n");
		*point = vec3_norm(*point);
	}
	return (0);
}

static void	parse_object_type(t_element *element, t_list *params)
{
	const char	*type = params->content;

	if (ft_strcmp(type, "sp") == 0)
	{
		element->type = SPHERE;
		element->params = read_sphere(params->next);
	}
	else if (ft_strcmp(type, "pl") == 0)
	{
		element->type = PLANE;
		element->params = read_plane(params->next);
	}
	else if (ft_strcmp(type, "cy") == 0)
	{
		element->type = CYLINDER;
		element->params = read_cylinder(params->next);
	}
}

int	read_element(t_vars *vars, t_list *element_params)
{
	t_element		*new_element;
	const char		*type;

	new_element = ft_calloc(1, sizeof(t_element));
	if (!new_element)
		return (print_error(NULL, ERR_ALC_MEM), 1);
	type = element_params->content;
	if (ft_strcmp(type, "A") == 0)
	{
		new_element->type = AMBIENT_LIGHTNING;
		new_element->params = read_ambient_lightning(element_params->next);
	}
	else if (ft_strcmp(type, "C") == 0)
	{
		new_element->type = CAMERA;
		new_element->params = read_camera(element_params->next);
	}
	else if (ft_strcmp(type, "L") == 0)
	{
		new_element->type = LIGHT;
		new_element->params = read_light(element_params->next);
	}
	else
		parse_object_type(new_element, element_params);
	if (new_element->type != 0 && new_element->params != NULL)
		add_element_to_list(vars, element_params, new_element);
	else if (ft_strncmp(type, "#", 1) != 0)
		return (print_error(NULL, ERR_WRNG_EL), free(new_element), 1);
	return (0);
}
