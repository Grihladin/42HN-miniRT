/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framebuffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:13:14 by psenko            #+#    #+#             */
/*   Updated: 2025/04/24 17:02:39 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_framebuffer(t_vars *vars)
{
	int		x;
	int		y;

	y = 0;
	while (y < vars->height)
	{
		x = 0;
		while (x < vars->width)
		{
			vars->frmbuf[y * vars->width + x].dist = INFINITY;
			vars->frmbuf[y * vars->width + x].color3
				= vec3_create(0.0f, 0.0f, 0.0f);
			x++;
		}
		y++;
	}
}

int	allocate_framebuffer(t_vars *vars)
{
	if (vars->frmbuf != NULL)
		free(vars->frmbuf);
	vars->frmbuf = ft_calloc((vars->width * vars->height),
			sizeof(t_frame));
	return (0);
}
