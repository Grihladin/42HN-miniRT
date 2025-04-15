/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:08:32 by psenko            #+#    #+#             */
/*   Updated: 2025/04/15 13:24:33 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	print_error(char *str, int type)
{
	ft_printf("Error\n");
	if (str == NULL)
		str = NULL;
	if (type == ERROR_COUNT_ARGUMENTS)
		ft_printf("Usage of command:\n./miniRT [filename]\n");
	else if (type == ERROR_ALLOCATE_MEMORY)
		ft_printf("Error allocate memory!\n");
	else if (type == ERROR_FATAL)
		ft_printf("Fatal Error!\n");
	else if (type == ERROR_ELEMENT_NOT_UNIQUE)
		ft_printf("Element %s is not unique!\n", str);
}
