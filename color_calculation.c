/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:55:50 by mratke            #+#    #+#             */
/*   Updated: 2025/04/15 20:00:28 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	color_multiply(t_color a, t_color b)
{
	return (vec3_create(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_color	color_scale(t_color c, float factor)
{
	return (vec3_create(c.x * factor, c.y * factor, c.z * factor));
}

t_color	color_sum(t_color a, t_color b)
{
	return (vec3_create(fminf(a.x + b.x, 1.0f), fminf(a.y + b.y, 1.0f),
			fminf(a.z + b.z, 1.0f)));
}
