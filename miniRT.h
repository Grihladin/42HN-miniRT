/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:07:24 by psenko            #+#    #+#             */
/*   Updated: 2025/04/17 12:29:17 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define DEFAULT_WIDTH 600
# define DEFAULT_HEIGHT 600
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
# define ERROR_WRONG_FILE_EXT 78
# define ERROR_COUNT_ARGUMENTS 14
# define ERROR_ELEMENT_NOT_UNIQUE 22
# define ERROR_ALLOCATE_MEMORY 122

# include "MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line_bonus.h"
# include "libft/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

// typedef struct s_color
// {
// 	unsigned char		red; //[0-255]
// 	unsigned char		green;
// 	unsigned char		blue;
// }						t_color;

typedef struct s_point
{
	float				x;
	float				y;
	float				z;
} t_vec3, t_point3,	t_color3;

typedef struct s_material
{
	t_color3			color;
	float				reflectivity;
}						t_material;

typedef struct s_ray
{
	t_point3			origin;
	t_vec3				direction;
}						t_ray;

typedef struct s_ambient_lightning
{
	float				amb_light_rate; //[0.0 , 1.0]
	t_color3			color;
}						t_ambient_lightning;

typedef struct s_camera
{
	t_point3			position;
	t_vec3				direction; // [-1,1]
	float				field_of_view; //[0,180]
	t_vec3				up;	//???What is it???
	// float				fov;
}						t_camera;

typedef struct s_light
{
	t_point3			position;
	float				brightness; //[0.0 , 1.0]
	t_color3			color;
}						t_light;

typedef struct s_scene
{
	t_ambient_lightning	*amb_light;
	t_camera			*camera;
	t_light				*light;
}						t_scene;

typedef struct s_sphere
{
	t_point3			center;
	float				diameter;
	float				radius;
	t_material			material;
}						t_sphere;

typedef struct s_plane
{
	t_point3			coord_point;
	t_vec3				normal_vector; // [-1,1]
	t_color3			color;
}						t_plane;

typedef struct s_cylinder
{
	t_point3			coord_center;
	t_vec3				normal_vector_axis_cyl; // [-1,1]
	float				diameter;
	float				height;
	t_color3			color;
}						t_cylinder;

typedef struct s_element
{
	char				type;
	void				*params;
}						t_element;

typedef struct s_vars
{
	mlx_t				*wind;
	mlx_image_t			*image;
	int					width;
	int					height;
	char				need_redraw;
	unsigned int		time_to_redraw;
	float				aspect_ratio;
	t_list				*elements;
	t_scene				scene;
	int					fd;
	t_color3			*framebuffer;
}						t_vars;

void					print_error(char *str, int type);
void					main_hook(void *param);

// hooks
void					key_hook(mlx_key_data_t keydata, void *param);
// void			scroll_hook(double xdelta, double ydelta, void *param);
void					close_hook(void *param);
// void			cursor_hook(double xpos, double ypos, void *param);
void					resize_hook(int width, int height, void *param);

// parsing
int						read_parameters(int argc, char **argv, t_vars *vars);
int						read_element(t_vars *vars, t_list *element_params);
t_point3				read_point(const char *str);
t_vec3					read_vector(const char *str);
t_color3				read_colors(const char *str);
t_light					*read_light(t_list *element_params);
t_sphere				*read_sphere(t_list *element_params);
t_plane					*read_plane(t_list *element_params);
t_cylinder				*read_cylinder(t_list *element_params);

// vector_operations
t_vec3					vec3_create(float x, float y, float z);
t_vec3					vec3_sum(t_vec3 a, t_vec3 b);
t_vec3					vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3					vec3_multiply(t_vec3 v, float scalar);
t_vec3					vec3_divide(t_vec3 v, float scalar);
t_vec3					vec3_cross(t_vec3 a, t_vec3 b);
t_vec3					vec3_normalize(t_vec3 v);
float					vec3_dot(t_vec3 a, t_vec3 b);
float					vec3_length(t_vec3 v);
float					calculate_distance(t_vec3 a, t_vec3 b);

// colors
t_color3				color_multiply(t_color3 a, t_color3 b);
t_color3				color_scale(t_color3 c, float factor);
t_color3				color_sum(t_color3 a, t_color3 b);

// utils
t_list					*rt_split(char *str);
float					ft_atof(const char *nptr);
void					free_arr_of_str(char ***strings);
void					delete_element(void *element);
int						check_unique_element(t_vars *vars, int type);
void					free_scene(t_scene *scene);

// Debug functions
void					print_elements(t_list *elements);
void					print_scene(t_scene *scene);

//Drawing
int						redraw_image(t_vars *vars);

void					raytrace(t_vars *vars, t_sphere *sphere);
void					out_image(t_vars *vars);

#endif


// typedef struct s_color
// {
// 	unsigned char red; //[0-255]
// 	unsigned char	green;
// 	unsigned char	blue;
// }					t_color;

// typedef struct s_point
// {
// 	float			x;
// 	float			y;
// 	float			z;
// } t_vec3, t_point3, t_color3;

// typedef struct s_ray
// {
// 	t_point3		origin;
// 	t_vec3			direction;
// }					t_ray;

// typedef struct s_material
// {
// 	t_color3		color;
// 	float			reflectivity;
// }					t_material;

// typedef struct s_sphere
// {
// 	t_point3		center;
// 	float			radius;
// 	t_material		material;
// }					t_sphere;

// typedef struct s_light
// {
// 	t_point3		position;
// 	t_color3		color;
// 	float			intensity;
// }					t_light;

// typedef struct s_scene
// {
// 	t_light			*light;
// 	t_sphere		*sphere;
// 	t_color3		ambient_light;
// }					t_scene;

// typedef struct s_camera
// {
// 	t_point3		position;
// 	t_vec3			direction;
// 	t_vec3			up;
// 	float			aspect_ratio;
// 	float			fov;
// }					t_camera;

// typedef struct s_vars
// {
// 	mlx_t			*wind;
// 	mlx_image_t		*image;
// 	int				width;
// 	int				height;
// 	char			need_redraw;
// 	unsigned int	time_to_redraw;
// 	t_scene			scene;
// 	int				fd;
// 	t_light			*light;
// 	t_camera		*camera;
// }					t_vars;
