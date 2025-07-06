/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:28:35 by psenko            #+#    #+#             */
/*   Updated: 2025/04/30 14:13:53 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	vec3_reverse(t_vec3 *vec)
{
	if (vec->y < -0.99800f)
		vec->y = 0.98f;
	else if (vec->y > 0.99800f)
		vec->y = -0.98f;
}

bool	vec3_is_norm(t_vec3 *vec)
{
	if (fabs(((*vec).x * (*vec).x) + ((*vec).y * (*vec).y)
			+ ((*vec).z * (*vec).z) - 1.0f) < EPSILON)
		return (1);
	return (0);
}
