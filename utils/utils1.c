/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:37:35 by psenko            #+#    #+#             */
/*   Updated: 2025/04/22 15:15:50 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	arr_size(char **arr)
{
	int		size;

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
	int		dot;

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

int	allocate_framebufer(t_vars *vars)
{
	if (vars->framebuffer != NULL)
		free(vars->framebuffer);
	vars->framebuffer = ft_calloc((vars->width * vars->height),
			sizeof(t_frame));
	return (0);
}
