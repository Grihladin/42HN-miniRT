/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:02:25 by psenko            #+#    #+#             */
/*   Updated: 2025/04/14 14:13:22 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	read_element(t_vars *vars, t_list *element_params)
{
	ft_printf("Read next element - %s\n", element_params->content);
	vars->elements = NULL;
	return (0);
}
