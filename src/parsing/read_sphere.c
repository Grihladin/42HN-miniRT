/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:12:17 by psenko            #+#    #+#             */
/*   Updated: 2025/04/30 15:20:00 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (is_pos_float_digit(element_params->content) == 0)
		return (free(new_sphere), print_error(NULL, ERR_PRM_NOT_NUMB), NULL);
	new_sphere->diameter = ft_atof(element_params->content);
	element_params = element_params->next;
	if (read_colors(element_params->content, &(new_sphere->material.color)))
		return (free(new_sphere), NULL);
	new_sphere->radius = new_sphere->diameter / 2;
	new_sphere->material.reflectivity = DEFAULT_REFLECTIVITY;
	return (new_sphere);
}
