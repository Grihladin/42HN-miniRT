/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:16:19 by mratke            #+#    #+#             */
/*   Updated: 2025/04/23 18:39:59 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
			- a.y * b.x));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float	length;

	length = vec3_length(v);
	if (length > 0)
		return (vec3_divide(v, length));
	return (v);
}

float	vec3_length(t_vec3 v)
{
	return (sqrtf(vec3_dot(v, v)));
}

float	calculate_distance(t_vec3 a, t_vec3 b)
{
	t_vec3	diff;

	diff = vec3_substract(a, b);
	return (vec3_length(diff));
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
