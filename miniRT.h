/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:07:24 by psenko            #+#    #+#             */
/*   Updated: 2025/04/14 11:06:32 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define DEFAULT_WIDTH 1200
# define DEFAULT_HEIGHT 1200
# define WINDOW_TITLE "One more COOL miniRT"

# include <math.h>
# include "libft/ft_printf.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <stdio.h>

typedef struct s_vars
{
	mlx_t			*wind;
	mlx_image_t		*image;
	unsigned int	width;
	unsigned int	height;
	char			need_redraw;
}				t_vars;

int				print_info(void);
int				read_parameters(int argc, char **argv, t_vars *vars);

void			main_hook(void *param);
void			key_hook(mlx_key_data_t keydata, void *param);
// void			scroll_hook(double xdelta, double ydelta, void *param);
void			close_hook(void *param);
// void			cursor_hook(double xpos, double ypos, void *param);
void			resize_hook(int width, int height, void *param);

#endif
