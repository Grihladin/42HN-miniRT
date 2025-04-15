/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:07:24 by psenko            #+#    #+#             */
/*   Updated: 2025/04/15 17:25:16 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define DEFAULT_WIDTH 1200
# define DEFAULT_HEIGHT 1200
# define TIMEOUT_BEFORE_UPDATE 10
# define WINDOW_TITLE "One more COOL miniRT"
# define AMBIENT_LIGHTNING 1
# define CAMERA 2
# define LIGHT 3
# define SPHERE 4
# define PLANE 5
# define CYLINDER 6

# define ERROR_GENERAL 1
# define ERROR_FATAL 2
# define ERROR_COUNT_ARGUMENTS 14
# define ERROR_ELEMENT_NOT_UNIQUE 22
# define ERROR_ALLOCATE_MEMORY 122

# include "MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line_bonus.h"
# include "libft/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

typedef struct s_colors
{
	unsigned char	red; //[0-255]
	unsigned char	green;
	unsigned char	blue;
}					t_colors;

typedef struct s_point
{
	float			x;
	float			y;
	float			z;
} t_vector3,	t_point;

typedef struct s_ray
{
	t_point			origin;
	t_vector3		direction;
}					t_ray;

typedef struct s_ambient_lightning
{
	float			amb_light_rate; //[0.0 , 1.0]
	t_colors		colors;
}					t_ambient_lightning;

typedef struct s_camera
{
	t_point			view_point;
	t_vector3		orient_vector;		// [-1,1]
	unsigned char	horizont_field_degree; //[0,180]
}					t_camera;

typedef struct s_light
{
	t_point			light_point;
	float			light_brightness; //[0.0 , 1.0]
}					t_light;

typedef struct s_sphere
{
	t_point			coord_center;
	float			diameter;
	float			radius;
	t_colors		colors;
}					t_sphere;

typedef struct s_plane
{
	t_point			coord_point;
	t_vector3		normal_vector; // [-1,1]
	t_colors		colors;
}					t_plane;

typedef struct s_cylinder
{
	t_point			coord_center;
	t_vector3		normal_vector_axis_cyl; // [-1,1]
	float			diameter;
	float			height;
	t_colors		colors;
}					t_cylinder;

typedef struct s_element
{
	char			type;
	void			*params;
}					t_element;

typedef struct s_vars
{
	mlx_t			*wind;
	mlx_image_t		*image;
	unsigned int	width;
	unsigned int	height;
	char			need_redraw;
	unsigned int	time_to_redraw;
	t_list			*elements;
	int				fd;
}					t_vars;

void				print_error(char *str, int type);
void				main_hook(void *param);

// hooks
void				key_hook(mlx_key_data_t keydata, void *param);
// void			scroll_hook(double xdelta, double ydelta, void *param);
void				close_hook(void *param);
// void			cursor_hook(double xpos, double ypos, void *param);
void				resize_hook(int width, int height, void *param);

// parsing
int					read_parameters(int argc, char **argv, t_vars *vars);
int					read_element(t_vars *vars, t_list *element_params);
t_point				read_point(const char *str);
t_vector3			read_vector(const char *str);
t_colors			read_colors(const char *str);
t_light				*read_light(t_list *element_params);
t_sphere			*read_sphere(t_list *element_params);
t_plane				*read_plane(t_list *element_params);
t_cylinder			*read_cylinder(t_list *element_params);

// vector_operations
t_vector3			vec3_create(float x, float y, float z);
t_vector3			vec3_add(t_vector3 a, t_vector3 b);
t_vector3			vec3_subtract(t_vector3 a, t_vector3 b);
t_vector3			vec3_multiply(t_vector3 v, float scalar);
t_vector3			vec3_divide(t_vector3 v, float scalar);
t_vector3			vec3_cross(t_vector3 a, t_vector3 b);
t_vector3			vec3_normalize(t_vector3 v);
float				vec3_dot(t_vector3 a, t_vector3 b);
float				vec3_length(t_vector3 v);
float				calculate_distance(t_vector3 a, t_vector3 b);

// utils
t_list				*rt_split(char *str);
float				ft_atof(const char *nptr);
void				free_arr_of_str(char ***strings);
void				delete_element(void *element);
void				print_elements(t_list *elements);
int					check_unique_element(t_list *elements, int type);

#endif
