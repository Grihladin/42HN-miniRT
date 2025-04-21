/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:08:14 by psenko            #+#    #+#             */
/*   Updated: 2025/04/21 13:13:07 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_ambient_lightning	*read_ambient_lightning(t_list *element_params)
{
	t_ambient_lightning		*new_amb_light;

	if (ft_lstsize(element_params) < 2)
		return (print_error(NULL, ERR_CNT_PARAMS), NULL);
	new_amb_light = ft_calloc(1, sizeof (t_ambient_lightning));
	if (new_amb_light == NULL)
		return (print_error(NULL, ERR_ALC_MEM), NULL);
	if (is_float_digit(element_params->content) == 0)
		return (free(new_amb_light),
			print_error(NULL, ERR_PRM_NOT_NUMB), NULL);
	new_amb_light->amb_light_rate = ft_atof(element_params->content);
	if ((new_amb_light->amb_light_rate < 0.0f)
		|| ((new_amb_light->amb_light_rate > 1.0f)))
		return (free(new_amb_light),
			print_error(NULL, ERR_VAL_NOT_IN_RANGE), NULL);
	element_params = element_params->next;
	if (read_colors(element_params->content, &(new_amb_light->color)))
		return (free(new_amb_light), NULL);
	return (new_amb_light);
}

t_camera	*read_camera(t_list *element_params)
{
	t_camera		*new_camera;

	if (ft_lstsize(element_params) < 3)
		return (print_error(NULL, ERR_CNT_PARAMS), NULL);
	new_camera = ft_calloc(1, sizeof (t_camera));
	if (new_camera == NULL)
		return (print_error(NULL, ERR_ALC_MEM), NULL);
	if (read_point(element_params->content, &(new_camera->position)))
		return (free(new_camera), NULL);
	element_params = element_params->next;
	if (read_vector(element_params->content, &(new_camera->direction)))
		return (free(new_camera), NULL);
	element_params = element_params->next;
	if (is_digits(element_params->content) == 0)
		return (free(new_camera),
			print_error(NULL, ERR_PRM_NOT_NUMB), NULL);
	new_camera->field_of_view = (float) ft_atoi(element_params->content);
	if ((new_camera->field_of_view < 0) || (new_camera->field_of_view > 180))
		return (print_error(NULL, ERR_VAL_NOT_IN_RANGE),
			free(new_camera), NULL);
	new_camera->up = vec3_create(0.0f, 1.0f, 0.0f);
	return (new_camera);
}
