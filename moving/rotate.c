/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:59:09 by psenko            #+#    #+#             */
/*   Updated: 2025/04/24 16:51:27 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	rotate_camera_hor(t_camera *camera, float angle)
{
	camera->direction.x = camera->direction.x * cosf(angle)
		- camera->direction.z * sinf(angle);
	camera->direction.z = camera->direction.x * sinf(angle)
		+ camera->direction.z * cosf(angle);
	camera->direction = vec3_normalize(camera->direction);
}

void	rotate_camera_vert(t_camera *camera, float angle)
{
	t_vec3	right;
	t_vec3	new_forward;

	right = vec3_normalize(vec3_cross(camera->direction, camera->up));
	new_forward = vec3_multiply(camera->direction, cosf(angle));
	new_forward.x += (right.y * camera->direction.z
			- right.z * camera->direction.y) * sinf(angle);
	new_forward.y += (right.z * camera->direction.x
			- right.x * camera->direction.z) * sinf(angle);
	new_forward.z += (right.x * camera->direction.y
			- right.y * camera->direction.x) * sinf(angle);
	camera->direction = vec3_normalize(new_forward);
	vec3_reverse(&(camera->direction));
}
