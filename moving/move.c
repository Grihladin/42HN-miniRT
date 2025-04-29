/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:53:27 by psenko            #+#    #+#             */
/*   Updated: 2025/04/29 19:23:34 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	move_camera_side(t_camera *camera, float distance)
{
	t_vec3	right;

	right = vec3_norm(vec3_cross(camera->direction, camera->up));
	camera->position = vec3_sum(camera->position,
			vec3_multiply(right, distance));
}
