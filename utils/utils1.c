/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:37:35 by psenko            #+#    #+#             */
/*   Updated: 2025/04/18 15:57:58 by psenko           ###   ########.fr       */
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
	ft_printf("Arr size: %d\n", size);
	return (size);
}
