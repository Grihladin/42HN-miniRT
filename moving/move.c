/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:53:27 by psenko            #+#    #+#             */
/*   Updated: 2025/07/06 01:03:44 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	move_camera_side(t_vars *vars, float distance)
{
	t_vec3	right;
	t_camera *camera;

	camera = vars->scene.camera;
	right = vec3_norm(vec3_cross(camera->direction, camera->up));
	camera->position = vec3_sum(camera->position,
			vec3_multiply(right, distance));
	invalidate_camera_cache(vars);
}
