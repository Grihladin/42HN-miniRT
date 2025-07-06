/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:55:50 by mratke            #+#    #+#             */
/*   Updated: 2025/04/22 09:35:44 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color3	color_multiply(t_color3 a, t_color3 b)
{
	return (vec3_create(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_color3	color_scale(t_color3 c, float factor)
{
	return (vec3_create(c.x * factor, c.y * factor, c.z * factor));
}

t_color3	color_sum(t_color3 a, t_color3 b)
{
	return (vec3_create(fminf(a.x + b.x, 1.0f), fminf(a.y + b.y, 1.0f),
			fminf(a.z + b.z, 1.0f)));
}
