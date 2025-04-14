/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:07:24 by psenko            #+#    #+#             */
/*   Updated: 2025/04/14 10:35:49 by psenko           ###   ########.fr       */
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

#endif
