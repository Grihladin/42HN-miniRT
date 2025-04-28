/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:07:24 by psenko            #+#    #+#             */
/*   Updated: 2025/04/28 20:52:02 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define DEFAULT_WIDTH 600
# define DEFAULT_HEIGHT 600
# define TIMEOUT_BEFORE_UPDATE 3
# define WINDOW_TITLE "One more COOL miniRT"
# define DEFAULT_REFLECTIVITY 0.1f
# define ROTATE_ANGLE 0.1f
# define MOUSE_ROTATE_ANGLE 0.05f
# define MOVE_DISTANCE 1.0f
# define AMBIENT_LIGHTNING 1
# define CAMERA 2
# define LIGHT 3
# define SPHERE 4
# define PLANE 5
# define CYLINDER 6

# define ERR_GEN 1
# define ERR_FATAL 2
# define ERR_CNT_ARG 14
# define ERR_EL_NOT_UNIQ 22
# define ERR_WRNG_FL_EXT 78
# define ERR_CRT_EL 79
# define ERR_CLR 80
# define ERR_CNT_PARAMS 81
# define ERR_VAL_NOT_IN_RANGE 82
# define ERR_PRM_NOT_NUMB 83
# define ERR_WRNG_EL 84
# define ERR_VEC_NOT_NORM 85
# define ERR_CRT_WNDW 86
# define ERR_MLX_IMG 87
# define ERR_ALC_MEM 122

# include "MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line_bonus.h"
# include "libft/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define EPSILON 0.001f

typedef struct s_color
{
	int					red;
	int					green;
	int					blue;
}						t_color;

typedef union t_color_int
{
	unsigned char		bytes[4];
	uint32_t			intgr;
}						t_color_int;

typedef struct s_point
{
	float				x;
	float				y;
	float				z;
} t_vec3, t_point3, t_color3;

typedef struct s_frame
{
	t_color3			color3;
	float				dist;
}						t_frame;

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

typedef struct s_hit_info
{
	bool				hit;
	float				t;
	t_point3			point;
	t_vec3				normal;
}						t_hit_info;

typedef struct s_ambient_lightning
{
	float				amb_light_rate;
	t_color3			color;
}						t_ambient_lightning;

typedef struct s_camera
{
	t_point3			position;
	t_vec3				direction;
	float				field_of_view;
	t_vec3				up;
}						t_camera;

typedef struct s_light
{
	t_point3			position;
	float				brightness;
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
	t_vec3				normal_vector;
	t_material			material;
}						t_plane;

typedef struct s_cylinder
{
	t_point3			coord_center;
	t_vec3				norm_vec_axis_cyl;
	float				diameter;
	float				height;
	t_material			material;
}						t_cylinder;

typedef struct s_element
{
	char				type;
	void				*params;
}						t_element;

typedef struct s_params
{
	float				a;
	float				b;
	float				c;
	t_vec3				oc;
	t_vec3				ray_dir_prep;
	t_vec3				oc_prep;
	float				discriminant;
}						t_params;

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
	t_frame				*frmbuf;
	double				cursor_xpos;
	double				cursor_ypos;
	int					mouse_rotate;
}						t_vars;

typedef struct s_lightning_calc
{
	t_light				light;
	t_vec3				light_dir;
	float				light_distance;
	float				diffuse_factor;
	t_vec3				reflection_dir;
	t_vec3				view_dir;
	t_ray				view_ray;
	float				specular_factor;
	float				attenuation;
	t_color3			diffuse;
	t_color3			specular;
	t_ray				shadow_ray;
	t_hit_info			hit;
}						t_lightning_calc;

void					print_error(char *str, int type);
void					print_str(char *str, int fd);
void					main_hook(void *param);

// hooks
void					key_hook(mlx_key_data_t keydata, void *param);
void					scroll_hook(double xdelta, double ydelta, void *param);
void					close_hook(void *param);
void					cursor_hook(double xpos, double ypos, void *param);
void					resize_hook(int width, int height, void *param);

// parsing
int						read_parameters(char **argv, t_vars *vars);
int						read_element(t_vars *vars, t_list *element_params);
int						read_point(const char *str, t_point3 *point);
int						read_vector(const char *str, t_point3 *point);
int						read_colors(const char *str, t_color3 *color);
t_light					*read_light(t_list *element_params);
t_sphere				*read_sphere(t_list *element_params);
t_plane					*read_plane(t_list *element_params);
t_cylinder				*read_cylinder(t_list *element_params);
t_ambient_lightning		*read_ambient_lightning(t_list *element_params);
t_camera				*read_camera(t_list *element_params);
int						add_element_to_list(t_vars *vars,
							t_list *element_params, t_element *new_element);

// vector_operations
t_vec3					vec3_create(float x, float y, float z);
t_vec3					vec3_sum(t_vec3 a, t_vec3 b);
t_vec3					vec3_substract(t_vec3 a, t_vec3 b);
t_vec3					vec3_multiply(t_vec3 v, float scalar);
t_vec3					vec3_divide(t_vec3 v, float scalar);
t_vec3					vec3_cross(t_vec3 a, t_vec3 b);
t_vec3					vec3_normalize(t_vec3 v);
float					vec3_dot(t_vec3 a, t_vec3 b);
float					vec3_length(t_vec3 v);
float					calculate_distance(t_vec3 a, t_vec3 b);
void					vec3_reverse(t_vec3 *vec);

// colors
t_color3				color_multiply(t_color3 a, t_color3 b);
t_color3				color_scale(t_color3 c, float factor);
t_color3				color_sum(t_color3 a, t_color3 b);
t_color3				calculate_lighting(t_vars *vars, t_hit_info hit,
							t_material material, t_ray view_ray);

// raytracing
t_ray					primary_ray(t_vars *vars, int i, int j);

// utils
int						arr_size(char **arr);
t_list					*rt_split(char *str);
float					ft_atof(const char *nptr);
void					free_arr_of_str(char ***strings);
void					delete_element(void *element);
int						check_unique_element(t_vars *vars, int type);
void					free_scene(t_scene *scene);
int						is_digits(char *str);
int						is_float_digit(char *str);
int						allocate_framebuffer(t_vars *vars);
void					free_framebuffer(t_vars *vars);

// Debug functions
void					print_elements(t_list *elements);
void					print_scene(t_scene *scene);

// Drawing
int						redraw_image(t_vars *vars);
void					out_image(t_vars *vars);

// Moving
void					zoom(t_camera *camera, float scale);
void					rotate_camera_vert(t_camera *camera, float angle);
void					rotate_camera_hor(t_camera *camera, float angle);
void					move_camera_side(t_camera *camera, float distance);

// raytracing
bool					is_in_bounds(t_cylinder *cylinder, t_point3 hit_point);
t_ray					primary_ray(t_vars *vars, int i, int j);
void					plane_calculation(t_vars *vars, t_plane *plane, int i,
							int j);
void					sphere_calculation(t_vars *vars, t_sphere *sphere,
							int i, int j);
void					cylinder_calculation(t_vars *vars, t_cylinder *cylinder,
							int i, int j);

bool					is_in_shadow(t_ray shadow_ray, t_list *elements,
							float max_t);
bool					intersect_sphere(t_ray ray, t_sphere *sphere, float *t,
							t_hit_info *hit);
bool					intersect_cylinder(t_ray ray, t_cylinder *cylinder,
							float *t, t_hit_info *hit);
t_hit_info				intersect_cylinder_body(t_ray ray,
							t_cylinder *cylinder);
t_hit_info				intersect_cylinder_cap(t_ray ray, t_cylinder *cylinder,
							bool is_top_cap);
bool					intersect_plane(t_ray ray, t_plane *plane, float *t,
							t_hit_info *hit);

void					before_exit(void *param);

#endif
