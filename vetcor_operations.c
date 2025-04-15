/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vetcor_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:06:26 by mratke            #+#    #+#             */
/*   Updated: 2025/04/15 16:22:14 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector3 vec3_create(float x, float y, float z)
{
	t_vector3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector3 vec3_add(t_vector3 a, t_vector3 b)
{
	return (vec3_create(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vector3 vec3_subtract(t_vector3 a, t_vector3 b)
{
	return (vec3_create(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vector3 vec3_multiply(t_vector3 v, float scalar)
{
	return (vec3_create(v.x * scalar, v.y * scalar, v.z * scalar));
}

t_vector3 vec3_divide(t_vector3 v, float scalar)
{
	return (vec3_create(v.x / scalar, v.y / scalar, v.z / scalar));
}

