/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:02:25 by psenko            #+#    #+#             */
/*   Updated: 2025/04/24 16:57:44 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	read_colors(const char *str, t_color3 *color)
{
	char			**colors_arr;
	t_color			color_int;

	colors_arr = ft_split(str, ',');
	if (arr_size(colors_arr) < 3)
		return (print_error(NULL, ERR_CLR), free_arr_of_str(&colors_arr), 1);
	if ((is_digits(colors_arr[0]) && is_digits(colors_arr[0])
			&& is_digits(colors_arr[0])) == 0)
		return (free_arr_of_str(&colors_arr),
			print_error(NULL, ERR_PRM_NOT_NUMB), 1);
	color_int.red = ft_atoi(colors_arr[0]);
	color_int.green = ft_atoi(colors_arr[1]);
	color_int.blue = ft_atoi(colors_arr[2]);
	if ((color_int.red < 0) || (color_int.red > 255)
		|| (color_int.green < 0) || (color_int.green > 255)
		|| (color_int.blue < 0) || (color_int.blue > 255))
		return (free_arr_of_str(&colors_arr), print_error(NULL, ERR_CLR), 1);
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
		return (print_error(NULL, ERR_CNT_PARAMS),
			free_arr_of_str(&point_arr), 1);
	if ((is_float_digit(point_arr[0]) && is_float_digit(point_arr[1])
			&& is_float_digit(point_arr[2])) == 0)
		return (free_arr_of_str(&point_arr),
			print_error(NULL, ERR_PRM_NOT_NUMB), 1);
	point->x = ft_atof(point_arr[0]);
	point->y = ft_atof(point_arr[1]);
	point->z = ft_atof(point_arr[2]);
	free_arr_of_str(&point_arr);
	return (0);
}

int	read_vector(const char *str, t_point3 *point)
{
	if (read_point(str, point) != 0)
		return (1);
	if ((point->x < -1.0f) || (point->x > 1.0f)
		|| (point->y < -1.0f) || (point->y > 1.0f)
		|| (point->z < -1.0f) || (point->z > 1.0f))
	{
		return (print_error(NULL, ERR_VAL_NOT_IN_RANGE), 1);
	}
	// Check normalization of vector???
	// if (vec3_length(*point) != 1)
	// 	return (print_error(NULL, ERR_VEC_NOT_NORM), 1);
	return (0);
}

void	read_element1(t_element **new_element, t_list *element_params)
{
	if (ft_strcmp(element_params->content, "sp") == 0)
	{
		(*new_element)->type = SPHERE;
		(*new_element)->params = read_sphere(element_params->next);
	}
	else if (ft_strcmp(element_params->content, "pl") == 0)
	{
		(*new_element)->type = PLANE;
		(*new_element)->params = read_plane(element_params->next);
	}
	else if (ft_strcmp(element_params->content, "cy") == 0)
	{
		(*new_element)->type = CYLINDER;
		(*new_element)->params = read_cylinder(element_params->next);
	}
}

int	read_element(t_vars *vars, t_list *element_params)
{
	t_element		*new_element;

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
	else
		read_element1(&new_element, element_params);
	if ((new_element->type != 0) && (new_element->params != NULL))
		add_element_to_list(vars, element_params, new_element);
	else if (ft_strncmp(element_params->content, "#", 1) != 0)
		return (print_error(NULL, ERR_WRNG_EL), free(new_element), 1);
	return (0);
}
