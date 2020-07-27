/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 18:13:41 by ttamesha          #+#    #+#             */
/*   Updated: 2020/07/26 00:17:53 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include <float.h>

# define FLAGS "0-+ #hlL"
# define SPC "c\%sdiuxXpnfego"
# define PREFIX "0 -+0x0X"

typedef struct	s_pf
{
	int			width;
	int			prec;
	int			f;
	int			sign;
	int			prefix;
	int			len;
	size_t		num;
	size_t		rm;
	long double	dbl;
}				t_pf;

enum
{
	capitals = 32,
	space = 1,
	plus = 3,
	minus = 2,
	zero = 4,
	hash = 8,
	l = 16,
	ll = 32,
	h = 64,
	hh = 128,
	e = 256,
	g = 512,
	L = 1024,
	inf = 2048,
	nan = 4096
};

union			u_dbl_union
{
	double		n_dbl;
	uint64_t	n_bits;
};

int				ft_printf(const char *str, ...);
char			calc_params(char c, t_pf *prm, va_list arg);
void			get_params(const char **str, t_pf *prm, va_list arg);

int				ft_min(int x, int y);
char			*ft_strchr(const char *str, int c);
void			ft_bzero(void *str, size_t n);
void			*ft_calloc(size_t nitems, size_t size);
void			*ft_memset(void *str, int c, size_t n);

int				print_num_base(size_t n, size_t bs, int len);
int				countdigits_base(size_t n, size_t bs);
int				count_len_uns(char c, t_pf *prm, va_list arg);
int				count_len_sn(t_pf *prm, va_list arg);

int				ft_putchar_intret(int c);
int				print_s(char *s, int len);
int				ft_strlen_pf(const char *str);

int				ft_putwchar(wint_t c);
int				print_ws(wchar_t *ws, int len);
int				ft_wcharlen(int c);
int				ft_wstrlen_pf(const wchar_t *str);

long double		ft_pow(long double n, size_t pow);
int				print_right_f(int len, t_pf *prm);
char			*left_part_f(long double n, int len);
char			*ft_itoa_f(size_t n, int len);
long double		get_arg_f(t_pf *prm, va_list arg);
char			*print_f_rest(long double n, int len);
int				countdigits_double(long double n);
void			check_inf_nan(uint64_t bits, t_pf *prm);
int				print_inf_nan(t_pf *prm);
void			g_set_prec(int x, t_pf *prm);
void			g_trim_zeroes(size_t *n, int *len, t_pf *prm);
void			g_correct_prec(t_pf *prm, int *len);
void			g_correct_prec_l(t_pf *prm, int *len);
int				int_part_len(long double *n, int len, t_pf *prm);
int				count_len_f(t_pf *prm, long double *n);
int				count_len_e(long double n, t_pf *prm);
int				calc_f(t_pf *prm, va_list arg);
int				calc_e(t_pf *prm, va_list arg);
int				calc_g(t_pf *prm, va_list arg);
int				print_float(t_pf *prm);
int				print_e(long double n, t_pf *prm);
int				print_g(long double n, t_pf *prm);
#endif
