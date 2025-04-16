/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:55:50 by mratke            #+#    #+#             */
/*   Updated: 2025/04/16 16:40:21 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colorf	colorf_create(float red, float green, float blue)
{
	t_colorf	c;

	c.red = red;
	c.green = green;
	c.blue = blue;
	return (c);
}

t_colorf	color_multiply(t_colorf a, t_colorf b)
{
	return (colorf_create(a.red * b.red, a.green * b.green, a.blue * b.blue));
}

t_colorf	color_scale(t_colorf c, float factor)
{
	return (colorf_create(c.red * factor, c.green * factor, c.blue * factor));
}

t_colorf	color_sum(t_colorf a, t_colorf b)
{
	return (colorf_create(fminf(a.red + b.red, 1.0f), fminf(a.green + b.green,
				1.0f), fminf(a.blue + b.blue, 1.0f)));
}
