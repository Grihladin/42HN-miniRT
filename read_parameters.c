/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:29:23 by psenko            #+#    #+#             */
/*   Updated: 2025/04/14 10:37:25 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	print_error(int typ)
{
	if (typ == 1)
		ft_printf("Wrong arguments!\n");
	print_info();
}

int	read_parameters(int argc, char **argv, t_vars *vars)
{
	if (argc > 1)
	{
		printf("%s\n", *argv);
		vars->need_redraw = 1;
	}
	else
		return (print_error(1), 1);
	return (0);
}
