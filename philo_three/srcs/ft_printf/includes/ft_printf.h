/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 04:27:31 by racohen           #+#    #+#             */
/*   Updated: 2019/11/18 22:00:39 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>
# include <stddef.h>
# include <stdio.h>

typedef struct	s_format
{
	char		type;
	size_t		len;
	int			width;
	int			justify;
	int			precision;
	int			o_char;
	int			is_zero;
	int			is_dot;
	int			is_min;
}				t_format;

int				ft_printf(const char *format, ...);
int				ft_atoi(const char *str);
int				ft_atoi_size(const char *str, int *size);
size_t			ft_strlen(const char *str);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_itoa(int nb);
char			*ft_itoa_u(unsigned int nb);
char			*ft_strdup(const char *str);
char			*ft_substr(const char *str, unsigned int start, size_t len);
char			*ft_freeall(char *res, t_format *form, int crit);
char			*parse_format(va_list *arg, char *format, int *size, char *res);
char			*ft_strjoinfree(char const *s1, char const *s2);
char			*ft_strjoinfreeboth(char *s1, char *s2, int lens1, int lens2);
char			*ft_min_just(t_format *form, char *res);
char			*hold_min(char *format, t_format *form, va_list *arg);
char			*hold_dot(char *format, t_format *form, va_list *arg);
char			*hold_zero(char *format, t_format *form, va_list *arg);
char			*hold_width(char *format, t_format *form, va_list *arg);
char			*ft_write_c(t_format *form, va_list *arg);
char			*ft_write_s(t_format *form, va_list *arg);
char			*ft_write_p(t_format *form, va_list *arg);
char			*ft_write_d(t_format *form, va_list *arg);
char			*ft_write_u(t_format *form, va_list *arg);
char			*ft_write_x(t_format *form, va_list *arg);
char			*ft_write_pr(t_format *form, va_list *arg);
t_format		*ft_setup_form(t_format *form);

#endif
