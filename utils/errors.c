/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:08:32 by psenko            #+#    #+#             */
/*   Updated: 2025/04/18 16:18:38 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	print_str(char *str, int fd)
{
	if (str != NULL)
		write(fd, str, ft_strlen(str));
}

void	print_error(char *str, int type)
{
	print_str("Error\n", 2);
	if (str == NULL)
		str = NULL;
	if (type == ERR_CNT_ARG)
		print_str("Usage of command:\n./miniRT [filename]\n", 2);
	else if (type == ERR_ALC_MEM)
		print_str("Error allocate memory!\n", 2);
	else if (type == ERR_FATAL)
		print_str("Fatal Error!\n", 2);
	else if (type == ERR_WRNG_FL_EXT)
	{
		print_str(str, 2);
		print_str(": Wrong file extension!\n", 2);
	}
	else if (type == ERR_CRT_EL)
		print_str("Error create elements!\n", 2);
	else if (type == ERR_EL_NOT_UNIQ)
	{
		print_str("Element ", 2);
		print_str(str, 2);
		print_str(" is not unique!\n", 2);
	}
}
