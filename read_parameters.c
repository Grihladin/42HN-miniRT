/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:29:23 by psenko            #+#    #+#             */
/*   Updated: 2025/04/14 14:13:19 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	print_error(int typ)
{
	ft_printf("Error\n");
	if (typ == 1)
		ft_printf("Wrong arguments!\n");
	if (typ == ERROR_FATAL)
		ft_printf("Fatal Error!\n");
	print_info();
}

int	read_parameters(int argc, char **argv, t_vars *vars)
{
	char	*nextstr;
	t_list	*element_params_list;

	if (argc > 1)
	{
		vars->fd = open(argv[1], O_RDONLY);
		if (vars->fd < 0)
			return (print_error(ERROR_FATAL), 1);
		nextstr = get_next_line(vars->fd);
		while (nextstr)
		{
			element_params_list = rt_split(nextstr);
			if (read_element(vars, element_params_list))
				return (print_error(ERROR_FATAL),
					ft_lstclear(&element_params_list, free), 1);
			nextstr = get_next_line(vars->fd);
		}
		close(vars->fd);
	}
	else
		return (print_error(1), 1);
	return (0);
}
