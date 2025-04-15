/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:35:57 by psenko            #+#    #+#             */
/*   Updated: 2025/04/15 09:36:08 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static const char	*skip_tabs(const char *s)
{
	while ((*s != '\0') && ((*s == ' ') || (*s == '\t')
			|| (*s == '\n') || (*s == '\v')
			|| (*s == '\f') || (*s == '\r')))
		s++;
	return (s);
}

static int	count_fract_part(const char *nptr)
{
	int		fract_size;

	fract_size = 0;
	while ((*nptr != '.') && (*nptr != '\0') && (*nptr >= 48) && (*nptr <= 57))
		nptr++;
	if (*nptr == '.')
		nptr++;
	while ((*nptr != '\0') && (*nptr >= 48) && (*nptr <= 57))
	{
		fract_size++;
		nptr++;
	}
	return (fract_size);
}

static int	atoi_min(const char *nptr)
{
	int	res;
	int	minus;

	res = 0;
	minus = 1;
	if (*nptr == '-')
	{
		minus = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while ((*nptr != '\0') && (((*nptr >= '0') && (*nptr <= '9'))
			|| (*nptr == '.')))
	{
		if (*nptr == '.')
			nptr++;
		res *= 10;
		res += (((int)*nptr) - 48) * minus;
		nptr++;
	}
	return (res);
}

float	ft_atof(const char *nptr)
{
	int		res;
	float	resf;

	res = 0;
	nptr = skip_tabs(nptr);
	res = atoi_min(nptr);
	if ((*nptr == '-') || (*nptr == '+'))
		nptr++;
	resf = (float)res / pow(10, count_fract_part(nptr));
	return (resf);
}
