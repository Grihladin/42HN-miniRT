/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:11:22 by psenko            #+#    #+#             */
/*   Updated: 2025/07/06 01:03:44 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	int			x;
	int			y;
	t_vars		*vars;

	vars = param;
	mlx_get_mouse_pos(vars->wind, &x, &y);
	if (ydelta > 0)
		zoom(vars->scene.camera, 3.0f);
	else if (ydelta < 0)
		zoom(vars->scene.camera, -3.0f);
	if (xdelta > 0)
		move_camera_side(vars, MOVE_DISTANCE);
	else if (xdelta < 0)
		move_camera_side(vars, -MOVE_DISTANCE);
	vars->need_redraw = 1;
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_vars		*vars;

	vars = param;
	if (vars->mouse_rotate)
	{
		if ((xpos <= vars->width) && (xpos >= 0)
			&& (ypos <= vars->height) && (ypos >= 0))
		{
			if ((ypos - vars->cursor_ypos) < 0)
				rotate_camera_vert(vars, MOUSE_ROTATE_ANGLE);
			else
				rotate_camera_vert(vars, -MOUSE_ROTATE_ANGLE);
			if ((xpos - vars->cursor_xpos) > 0)
				rotate_camera_hor(vars, MOUSE_ROTATE_ANGLE);
			else
				rotate_camera_hor(vars, -MOUSE_ROTATE_ANGLE);
			vars->cursor_xpos = xpos;
			vars->cursor_ypos = ypos;
			vars->need_redraw = 1;
		}
	}
}
