/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:19:10 by psenko            #+#    #+#             */
/*   Updated: 2025/04/21 13:15:43 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_light	*read_light(t_list *element_params)
{
	t_light		*new_light;

	if (ft_lstsize(element_params) < 3)
		return (print_error(NULL, ERR_CNT_PARAMS), NULL);
	new_light = ft_calloc(1, sizeof (t_light));
	if (new_light == NULL)
		return (print_error(NULL, ERR_ALC_MEM), NULL);
	if (read_point(element_params->content, &(new_light->position)))
		return (free(new_light), NULL);
	element_params = element_params->next;
	if (is_float_digit(element_params->content) == 0)
		return (free(new_light), print_error(NULL, ERR_PRM_NOT_NUMB), NULL);
	new_light->brightness = ft_atof(element_params->content);
	if ((new_light->brightness < 0.0f)
		|| ((new_light->brightness > 1.0f)))
		return (free(new_light), print_error(NULL, ERR_VAL_NOT_IN_RANGE), NULL);
	new_light->brightness *= 1000;
	element_params = element_params->next;
	if (read_colors(element_params->content, &(new_light->color)))
		return (free(new_light), NULL);
	return (new_light);
}

t_sphere	*read_sphere(t_list *element_params)
{
	t_sphere		*new_sphere;

	if (ft_lstsize(element_params) < 3)
		return (print_error(NULL, ERR_CNT_PARAMS), NULL);
	new_sphere = ft_calloc(1, sizeof (t_sphere));
	if (new_sphere == NULL)
		return (print_error(NULL, ERR_ALC_MEM), NULL);
	if (read_point(element_params->content, &(new_sphere->center)))
		return (free(new_sphere), NULL);
	element_params = element_params->next;
	if (is_float_digit(element_params->content) == 0)
		return (free(new_sphere), print_error(NULL, ERR_PRM_NOT_NUMB), NULL);
	new_sphere->diameter = ft_atof(element_params->content);
	element_params = element_params->next;
	if (read_colors(element_params->content, &(new_sphere->material.color)))
		return (free(new_sphere), NULL);
	new_sphere->radius = new_sphere->diameter / 2;
	new_sphere->material.reflectivity = DEFAULT_REFLECTIVITY;
	return (new_sphere);
}

t_plane	*read_plane(t_list *element_params)
{
	t_plane		*new_plane;

	if (ft_lstsize(element_params) < 3)
		return (print_error(NULL, ERR_CNT_PARAMS), NULL);
	new_plane = ft_calloc(1, sizeof (t_plane));
	if (new_plane == NULL)
		return (print_error(NULL, ERR_ALC_MEM), NULL);
	if (read_point(element_params->content, &(new_plane->coord_point)))
		return (free(new_plane), NULL);
	element_params = element_params->next;
	if (read_vector(element_params->content, &(new_plane->normal_vector)))
		return (free(new_plane), NULL);
	element_params = element_params->next;
	if (read_colors(element_params->content, &(new_plane->material.color)))
		return (free(new_plane), NULL);
	new_plane->material.reflectivity = DEFAULT_REFLECTIVITY;
	return (new_plane);
}

t_cylinder	*read_cylinder(t_list *element_params)
{
	t_cylinder		*new_cylinder;

	if (ft_lstsize(element_params) < 4)
		return (print_error(NULL, ERR_CNT_PARAMS), NULL);
	new_cylinder = ft_calloc(1, sizeof (t_cylinder));
	if (new_cylinder == NULL)
		return (print_error(NULL, ERR_ALC_MEM), NULL);
	if (read_point(element_params->content, &(new_cylinder->coord_center)))
		return (free(new_cylinder), NULL);
	element_params = element_params->next;
	if (read_vector(element_params->content,
			&(new_cylinder->norm_vec_axis_cyl)))
		return (free(new_cylinder), NULL);
	element_params = element_params->next;
	if ((is_float_digit(element_params->content) == 0)
		|| (is_float_digit(element_params->next->content) == 0))
		return (free(new_cylinder), print_error(NULL, ERR_PRM_NOT_NUMB), NULL);
	new_cylinder->diameter = ft_atof(element_params->content);
	element_params = element_params->next;
	new_cylinder->height = ft_atof(element_params->content);
	element_params = element_params->next;
	if (read_colors(element_params->content, &(new_cylinder->material.color)))
		return (free(new_cylinder), NULL);
	new_cylinder->material.reflectivity = DEFAULT_REFLECTIVITY;
	return (new_cylinder);
}
