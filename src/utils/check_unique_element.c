/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unique_element.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:02:54 by psenko            #+#    #+#             */
/*   Updated: 2025/04/16 11:30:46 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_unique_element(t_vars *vars, int type)
{
	if (((type == AMBIENT_LIGHTNING) && (vars->scene.amb_light != NULL))
		|| ((type == CAMERA) && (vars->scene.camera != NULL))
		|| ((type == LIGHT) && (vars->scene.light != NULL)))
		return (1);
	return (0);
}
