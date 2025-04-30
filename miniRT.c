/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:07:33 by psenko            #+#    #+#             */
/*   Updated: 2025/04/30 14:47:37 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_vars(struct s_vars *vars)
{
	vars->wind = NULL;
	vars->image = NULL;
	vars->width = DEFAULT_WIDTH;
	vars->height = DEFAULT_HEIGHT;
	vars->need_redraw = 1;
	vars->time_to_redraw = 0;
	vars->elements = NULL;
	vars->fd = -1;
	vars->scene.amb_light = NULL;
	vars->scene.camera = NULL;
	vars->scene.light = NULL;
	vars->cursor_xpos = 0;
	vars->cursor_ypos = 0;
	vars->mouse_rotate = 0;
	vars->aspect_ratio = vars->width / vars->height;
	vars->frmbuf = NULL;
	allocate_framebuffer(vars);
	if (vars->frmbuf == NULL)
	{
		print_error(NULL, ERR_ALC_MEM);
		return (1);
	}
	return (0);
}

void	before_exit(void *param)
{
	t_vars	*vars;

	vars = param;
	free(vars->frmbuf);
	free_scene(&(vars->scene));
	ft_lstclear(&(vars->elements), delete_element);
	if (vars->wind != NULL)
	{
		if (vars->image != NULL)
			mlx_delete_image(vars->wind, vars->image);
		mlx_terminate(vars->wind);
	}
}

int	prepare_mlx(t_vars *vars)
{
	vars->wind = mlx_init(vars->width, vars->height, WINDOW_TITLE, 1);
	if (vars->wind == NULL)
		return (print_error(NULL, ERR_CRT_WNDW), 1);
	vars->image = mlx_new_image(vars->wind, vars->width, vars->height);
	ft_memset(vars->image->pixels, 255, vars->image->width * vars->image->height
		* sizeof(int32_t));
	if ((vars->image == NULL) || (mlx_image_to_window(vars->wind, vars->image,
				0, 0) < 0))
		return (print_error(NULL, ERR_MLX_IMG), 1);
	mlx_key_hook(vars->wind, key_hook, vars);
	mlx_loop_hook(vars->wind, main_hook, vars);
	mlx_scroll_hook(vars->wind, scroll_hook, vars);
	mlx_resize_hook(vars->wind, resize_hook, vars);
	mlx_cursor_hook(vars->wind, cursor_hook, vars);
	mlx_close_hook(vars->wind, close_hook, vars);
	return (0);
}

static int	preparations(int argc, char **argv, t_vars *vars)
{
	if (init_vars(vars))
		return (1);
	if (argc > 1)
	{
		if (read_parameters(argv, vars) == 1)
			return (1);
		if ((vars->scene.amb_light == NULL) || (vars->scene.camera == NULL)
			|| (vars->scene.light == NULL))
			return (print_error(NULL, ERR_WRNG_EL), 1);
	}
	else
		return (print_error(NULL, ERR_GEN), 1);
	if (prepare_mlx(vars))
		return (print_error(NULL, ERR_GEN), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc == 1)
		return (print_error(NULL, ERR_CNT_ARG), 1);
	if (preparations(argc, argv, &vars) == 1)
	{
		before_exit(&vars);
		return (1);
	}
	mlx_loop(vars.wind);
	before_exit(&vars);
	return (0);
}
