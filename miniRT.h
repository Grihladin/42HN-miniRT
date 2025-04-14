/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:07:24 by psenko            #+#    #+#             */
/*   Updated: 2025/04/14 14:01:19 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define DEFAULT_WIDTH 1200
# define DEFAULT_HEIGHT 1200
# define WINDOW_TITLE "One more COOL miniRT"
# define AMBIENT_LIGHTNING 1
# define CAMERA 2
# define LIGHT 3
# define SPHERE 4
# define PLANE 5
# define CYLINDER 6

# define ERROR_FATAL 2

# include <math.h>
# include "libft/ft_printf.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include "get_next_line/get_next_line_bonus.h"

typedef struct s_colors
{
	unsigned char	red;			//[0-255]
	unsigned char	green;
	unsigned char	blue;
}				t_colors;

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;

typedef struct s_ambient_lightning
{
	float			amb_light_rate;		//[0.0 , 1.0]
	t_colors		colors;
}				t_ambient_lightning;

typedef struct s_camera
{
	t_point			view_point;
	t_point			orient_vector;			// [-1,1]
	unsigned char	horizont_field_degree;	//[0,180]
}				t_camera;

typedef struct s_light
{
	t_point			light_point;
	float			light_brightness;	//[0.0 , 1.0]
}				t_light;

typedef struct s_sphere
{
	t_point			coord_center;
	float			diameter;
	t_colors		colors;
}				t_sphere;

typedef struct s_plane
{
	t_point			coord_point;
	t_point			normal_vector;	// [-1,1]
}				t_plane;

typedef struct s_cylinder
{
	t_point			coord_center;
	t_point			normal_vector_axis_cyl;		// [-1,1]
	float			diameter;
	float			height;
	t_colors		colors;
}				t_cylinder;

typedef struct s_element
{
	char		type;
	void		*params;
}				t_element;

typedef struct s_vars
{
	mlx_t			*wind;
	mlx_image_t		*image;
	unsigned int	width;
	unsigned int	height;
	char			need_redraw;
	t_list			*elements;
	int				fd;
}				t_vars;

int				print_info(void);
int				read_parameters(int argc, char **argv, t_vars *vars);
t_list			*rt_split(char *str);
int				read_element(t_vars *vars, t_list *element_params);

void			main_hook(void *param);
void			key_hook(mlx_key_data_t keydata, void *param);
// void			scroll_hook(double xdelta, double ydelta, void *param);
void			close_hook(void *param);
// void			cursor_hook(double xpos, double ypos, void *param);
void			resize_hook(int width, int height, void *param);

#endif
