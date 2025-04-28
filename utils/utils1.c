/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:37:35 by psenko            #+#    #+#             */
/*   Updated: 2025/04/28 20:15:31 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

bool	is_in_bounds(t_cylinder *cylinder, t_point3 hit_point)
{
	float	projection;
	t_vec3	vec_to_hit;

	vec_to_hit = vec3_substract(hit_point, cylinder->coord_center);
	projection = vec3_dot(vec_to_hit, cylinder->norm_vec_axis_cyl);
	return (projection >= -cylinder->height / 2.0f
		&& projection <= cylinder->height / 2.0f);
}

int	arr_size(char **arr)
{
	int	size;

	size = 0;
	while (*arr != NULL)
	{
		size++;
		arr++;
	}
	return (size);
}

int	is_digits(char *str)
{
	if (*str == '-')
		str++;
	while (*str != '\0')
	{
		if ((*str < '0') || (*str > '9'))
			return (0);
		str++;
	}
	return (1);
}

int	is_float_digit(char *str)
{
	int	dot;

	if (*str == '-')
		str++;
	dot = 0;
	while (*str != '\0')
	{
		if ((*str == '.') && !dot)
			dot = 1;
		else if ((*str == '.') && dot)
			return (0);
		else if ((*str < '0') || (*str > '9'))
			return (0);
		str++;
	}
	return (1);
}
