/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:48:28 by psenko            #+#    #+#             */
/*   Updated: 2024/10/13 13:48:14 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_rec1(int fd, int n, int minus)
{
	int				div;
	unsigned char	rest;

	div = n / 10;
	rest = (char)(((int) n % 10) * (int) minus) + 48;
	if (div != 0)
		ft_itoa_rec1(fd, div, minus);
	write(fd, &rest, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		minus;
	char	minus_ch;

	minus = 1;
	minus_ch = '-';
	if (n < 0)
	{
		write(fd, &minus_ch, 1);
		minus = -1;
	}
	ft_itoa_rec1(fd, n, minus);
}
