/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:08:32 by psenko            #+#    #+#             */
/*   Updated: 2025/04/22 15:32:02 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	print_str(char *str, int fd)
{
	if (str != NULL)
		write(fd, str, ft_strlen(str));
}

static void	print_error1(int type)
{
	if (type == ERR_CLR)
		print_str("Wrong color!\n", 2);
	else if (type == ERR_VAL_NOT_IN_RANGE)
		print_str("Value not in range!\n", 2);
	else if (type == ERR_PRM_NOT_NUMB)
		print_str("Parameter is not correct number!\n", 2);
	else if (type == ERR_WRNG_EL)
		print_str("Wrong element in file!\n", 2);
	else if (type == ERR_VEC_NOT_NORM)
		print_str("Vector is not normilized!\n", 2);
	else if (type == ERR_CRT_WNDW)
		print_str("Create window!\n", 2);
	else if (type == ERR_MLX_IMG)
		print_str("MLX image!\n", 2);
}

void	print_error(char *str, int type)
{
	print_str("Error\n", 2);
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
	else if (type == ERR_CNT_PARAMS)
		print_str("Wrong count of parameters!\n", 2);
	else
		print_error1(type);
}
