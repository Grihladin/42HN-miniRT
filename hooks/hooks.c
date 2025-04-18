/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:01:02 by psenko            #+#    #+#             */
/*   Updated: 2025/04/18 15:33:04 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	main_hook(void *param)
{
	t_vars		*vars;

	vars = param;
	if ((vars->need_redraw == 1) && (vars->time_to_redraw
			>= TIMEOUT_BEFORE_UPDATE))
	{
		redraw_image(vars);
		vars->need_redraw = 0;
		vars->time_to_redraw = 0;
	}
	else if (vars->time_to_redraw < TIMEOUT_BEFORE_UPDATE)
		vars->time_to_redraw++;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_vars		*vars;

	vars = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(vars->wind);
	if ((keydata.action == MLX_PRESS) || (keydata.action == MLX_REPEAT))
	{
		if (keydata.key == MLX_KEY_W)
			zoom(vars->scene.camera, 1.0f);
		if (keydata.key == MLX_KEY_S)
			zoom(vars->scene.camera, -1.0f);
		if (keydata.key == MLX_KEY_S)
			zoom(vars->scene.camera, -1.0f);
		if (keydata.key == MLX_KEY_UP)
			rotate_camera_vert(vars->scene.camera, ROTATE_ANGLE);
		if (keydata.key == MLX_KEY_DOWN)
			rotate_camera_vert(vars->scene.camera, -ROTATE_ANGLE);
		if (keydata.key == MLX_KEY_LEFT)
			rotate_camera_hor(vars->scene.camera, -ROTATE_ANGLE);
		if (keydata.key == MLX_KEY_RIGHT)
			rotate_camera_hor(vars->scene.camera, ROTATE_ANGLE);
		if (keydata.key == MLX_KEY_A)
			move_camera_side(vars->scene.camera, -MOVE_DISTANCE);
		if (keydata.key == MLX_KEY_D)
			move_camera_side(vars->scene.camera, MOVE_DISTANCE);
		if (keydata.key == MLX_KEY_M)
			vars->mouse_rotate ^= 1;
	}
	if (((keydata.key == MLX_KEY_UP) || (keydata.key == MLX_KEY_DOWN)
			|| (keydata.key == MLX_KEY_LEFT) || (keydata.key == MLX_KEY_RIGHT)
			|| (keydata.key == MLX_KEY_W) || (keydata.key == MLX_KEY_S)
			|| (keydata.key == MLX_KEY_A) || (keydata.key == MLX_KEY_D)
			|| (keydata.key == MLX_KEY_ENTER))
		&& ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		vars->need_redraw = 1;
}

void	resize_hook(int width, int height, void *param)
{
	t_vars		*vars;

	vars = param;
	vars->width = width;
	vars->height = height;
	vars->aspect_ratio = (float) vars->width / (float) vars->height;
	free(vars->framebuffer);
	vars->framebuffer = ft_calloc((vars->width * vars->height),
			sizeof(t_color3));
	mlx_resize_image(vars->image, width, height);
	vars->need_redraw = 1;
	return ;
}

void	close_hook(void *param)
{
	t_vars		*vars;

	vars = param;
	mlx_close_window(vars->wind);
}
