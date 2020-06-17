/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:57:59 by racohen           #+#    #+#             */
/*   Updated: 2019/11/12 21:34:15 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*add_content_res(char *res, t_format *form, va_list *arg, int size)
{
	if (form->type == 'c')
		res = ft_strjoinfreeboth(res, ft_write_c(form, arg), size, form->width);
	else if (form->type == 's')
		res = ft_strjoinfreeboth(res, ft_write_s(form, arg), size, form->width);
	else if (form->type == 'p')
		res = ft_strjoinfreeboth(res, ft_write_p(form, arg), size, form->width);
	else if (form->type == 'd')
		res = ft_strjoinfreeboth(res, ft_write_d(form, arg), size, form->width);
	else if (form->type == 'i')
		res = ft_strjoinfreeboth(res, ft_write_d(form, arg), size, form->width);
	else if (form->type == 'u')
		res = ft_strjoinfreeboth(res, ft_write_u(form, arg), size, form->width);
	else if (form->type == 'x')
		res = ft_strjoinfreeboth(res, ft_write_x(form, arg), size, form->width);
	else if (form->type == 'X')
		res = ft_strjoinfreeboth(res, ft_write_x(form, arg), size, form->width);
	else
		res = ft_strjoinfreeboth(res,
			ft_write_pr(form, arg), size, form->width);
	return (res);
}

int		is_convert(char c, t_format *form)
{
	if (c != '-' && c != '.' && c != '0' && c != '*' && !(c >= '0' && c <= '9'))
	{
		form->type = c;
		return (1);
	}
	return (0);
}

int		ft_parse_mod(char **format, t_format **form, va_list *arg)
{
	int empty;

	empty = 0;
	(*format) += 1;
	while (*(*format) != '\0' && is_convert(*(*format), *form) != 1)
	{
		if (*(*format) == '-')
			*format = hold_min((*format) + 1, *form, arg);
		else if (*(*format) == '0')
			*format = hold_zero((*format) + 1, *form, arg);
		else if (*(*format) == '.')
			*format = hold_dot((*format) + 1, *form, arg);
		else if (((*(*format)) >= '0' && (*(*format)) <= '9')
				|| *(*format) == '*')
			*format = hold_width((*format), *form, arg);
		else
		{
			empty = 1;
			break ;
		}
	}
	if (empty)
		return (0);
	(*format) += 1;
	return (1);
}

char	*parse_format(va_list *arg, char *format, int *size, char *res)
{
	t_format	*form;

	form = NULL;
	while (*format)
	{
		if ((form = ft_setup_form(form)) == NULL)
			return (ft_freeall(res, form, 1));
		if (*format == '%' && *(format + 1) != '\0')
		{
			if (ft_parse_mod(&format, &form, arg))
				if ((res = add_content_res(res, form, arg, *size)) == NULL)
					return (ft_freeall(res, form, 1));
		}
		else
		{
			if ((res = ft_strjoinfreeboth(res, ft_substr(format, 0, 1),
				*size, 1)) == NULL)
				return (ft_freeall(res, form, 1));
			format++;
			*size += 1;
		}
		*size += form->width;
		free(form);
	}
	return (res);
}
