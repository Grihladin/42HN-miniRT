/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:29:23 by psenko            #+#    #+#             */
/*   Updated: 2025/04/30 10:39:54 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	read_parameters(char **argv, t_vars *vars)
{
	char	*nextstr;
	t_list	*element_params_list;
	char	**filename;

	filename = ft_split(argv[1], '.');
	if ((arr_size(filename) < 2) || ft_strcmp(filename[1], "rt"))
		return (print_error(argv[1], ERR_WRNG_FL_EXT), 1);
	free_arr_of_str(&filename);
	vars->fd = open(argv[1], O_RDONLY);
	if (vars->fd < 0)
		return (print_error(NULL, ERR_FATAL), 1);
	nextstr = get_next_line(vars->fd);
	while (nextstr)
	{
		element_params_list = rt_split(nextstr);
		if (read_element(vars, element_params_list))
			return (ft_lstclear(&element_params_list, free),
				ft_lstclear(&element_params_list, free), 1);
		ft_lstclear(&element_params_list, free);
		free(nextstr);
		nextstr = get_next_line(vars->fd);
	}
	close(vars->fd);
	return (0);
}
