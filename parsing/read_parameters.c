/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:29:23 by psenko            #+#    #+#             */
/*   Updated: 2025/04/15 13:22:04 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	read_parameters(int argc, char **argv, t_vars *vars)
{
	char	*nextstr;
	t_list	*element_params_list;

	if (argc > 1)
	{
		vars->fd = open(argv[1], O_RDONLY);
		if (vars->fd < 0)
			return (print_error(NULL, ERROR_FATAL), 1);
		nextstr = get_next_line(vars->fd);
		while (nextstr)
		{
			element_params_list = rt_split(nextstr);
			if (read_element(vars, element_params_list))
				return (ft_lstclear(&element_params_list, free),
					ft_lstclear(&element_params_list, free), 1);
			ft_lstclear(&element_params_list, free);
			nextstr = get_next_line(vars->fd);
		}
		close(vars->fd);
	}
	else
		return (print_error(NULL, ERROR_GENERAL), 1);
	print_elements(vars->elements);
	ft_lstclear(&(vars->elements), delete_element);
	return (0);
}
