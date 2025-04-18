/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:36:03 by psenko            #+#    #+#             */
/*   Updated: 2025/04/18 12:10:05 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	zoom(t_camera *camera, float scale)
{
	camera->position = vec3_sum(camera->position,
			vec3_multiply(camera->direction, scale));
}
