/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:07:33 by psenko            #+#    #+#             */
/*   Updated: 2025/04/14 13:11:32 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_vars(struct s_vars *vars)
{
	vars->wind = NULL;
	vars->image = NULL;
	vars->width = DEFAULT_WIDTH;
	vars->height = DEFAULT_HEIGHT;
	vars->need_redraw = 1;
	vars->fd = -1;
}

void	before_exit(void *param)
{
	t_vars		*vars;

	vars = param;
	if (vars->wind != NULL)
	{
		if (vars->image != NULL)
			mlx_delete_image(vars->wind, vars->image);
		mlx_terminate(vars->wind);
	}
}

static int	preparations(int argc, char **argv, struct s_vars *vars)
{
	init_vars(vars);
	if (argc == 1)
		return (print_info(), 1);
	if (read_parameters(argc, argv, vars) == 1)
		return (1);
	vars->wind = mlx_init(vars->width, vars->height, WINDOW_TITLE, 1);
	if (vars->wind == NULL)
		return (perror("Create window"), 1);
	vars->image = mlx_new_image(vars->wind, vars->width, vars->height);
	ft_memset(vars->image->pixels, 255, vars->image->width
		* vars->image->height * sizeof(int32_t));
	if ((vars->image == NULL)
		|| (mlx_image_to_window(vars->wind, vars->image, 0, 0) < 0))
		return (perror("Output image"), 1);
	mlx_key_hook(vars->wind, key_hook, vars);
	mlx_loop_hook(vars->wind, main_hook, vars);
	// mlx_scroll_hook(vars->wind, scroll_hook, vars);
	mlx_resize_hook(vars->wind, resize_hook, vars);
	mlx_close_hook(vars->wind, close_hook, vars);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars		vars;

	if (preparations(argc, argv, &vars) == 1)
	{
		before_exit(&vars);
		return (1);
	}
	mlx_loop(vars.wind);
	before_exit(&vars);
	return (0);
}
