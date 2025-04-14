/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:53:45 by psenko            #+#    #+#             */
/*   Updated: 2024/11/28 13:37:49 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct s_format
{
	char	typ;
	char	minus;
	char	plus;
	char	space;
	char	zero;
	int		maxlen;
	int		minlen;
	char	hash;
	char	dot;
	int		cnt_skip;
	char	err;
	char	ch;
	char	negative;
}			t_format;
void		init_type(t_format *type);

int			ft_printf(const char *src, ...);
int			ft_putnbru_cnt(unsigned int n, int *cnt, t_format *type);
int			ft_putnbrx_cnt(unsigned int n, int *cnt, t_format *type);
int			ft_put_pointer_cnt(void *pnt, int fd, int *cnt, t_format *type);
int			ft_putchar_cnt(char c, int fd, int *cnt);
int			ft_putchar_cnt_typ(char c, int fd, int *cnt, t_format *type);
int			ft_putchar_typ(char c, int fd, int *cnt, t_format *type);
int			ft_putstr_typ(char *s, int fd, int *cnt, t_format *type);
int			ft_putstr_cnt(char *s, int fd, int *cnt);
int			ft_putnbr_cnt(int n, int *cnt, t_format *type);
int			ft_putpr_cnt(int *cnt, t_format *type);
int			ft_putnbru_out(unsigned int n, int base, int hex_case, int *cnt);

int			ft_get_format(const char *str, t_format *type);
int			check_it_format(char ch);
void		get_modified_x(const char *str, t_format *type);
void		get_modified_id(const char *str, t_format *type);
void		get_modified_ch(const char *str, t_format *type);
void		get_modified_str(const char *str, t_format *type);
void		get_modified_p(const char *str, t_format *type);
void		get_modified_u(const char *str, t_format *type);
void		get_modified_pr(const char *str, t_format *type);
void		check_null_minus(const char **str, t_format *type);
void		check_minus(const char **str, t_format *type);
void		check_plus(const char **str, t_format *type);
void		check_space(const char **str, t_format *type);
char		check_dot(const char **str);
void		check_hash(const char **str, t_format *type);
int			get_num(const char **str);

#endif
