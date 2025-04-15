/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:01:02 by psenko            #+#    #+#             */
/*   Updated: 2025/04/15 12:59:00 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	main_hook(void *param)
{
	t_vars		*vars;

	vars = param;
	if ((vars->need_redraw == 1) && (vars->time_to_redraw
			>= TIMEOUT_BEFORE_UPDATE))
	{
		// paint_fractal(vars);
		ft_printf("Redraw\n");
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
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
		vars->need_redraw = 1;
}

// void	scroll_hook(double xdelta, double ydelta, void *param)
// {
// 	t_vars		*vars;

// 	vars = param;
// 	mlx_get_mouse_pos(vars->wind, &x, &y);
// 	get_coordinats(x, y, &z1, vars);
// 	if (ydelta > 0)
// 		vars->scale *= SCALE_OFFSET;
// 	else if (ydelta < 0)
// 		vars->scale /= SCALE_OFFSET;
// 	get_coordinats(x, y, &z2, vars);
// 	set_redraw(vars);
// }

void	resize_hook(int width, int height, void *param)
{
	t_vars		*vars;

	vars = param;
	mlx_resize_image(vars->image, width, height);
	vars->width = width;
	vars->height = height;
	vars->need_redraw = 1;
	return ;
}

void	close_hook(void *param)
{
	t_vars		*vars;

	vars = param;
	mlx_close_window(vars->wind);
}
