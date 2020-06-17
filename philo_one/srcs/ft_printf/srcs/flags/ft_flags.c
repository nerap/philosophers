/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 21:50:36 by racohen           #+#    #+#             */
/*   Updated: 2019/11/11 21:30:07 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*hold_min(char *format, t_format *form, va_list *arg)
{
	int	tmp;
	int	size;

	size = 0;
	tmp = 0;
	if (*format == '*')
		tmp = va_arg(*arg, int);
	else if (*format == '-')
		size = 1;
	else
		tmp = ft_atoi_size(format, &size);
	if (tmp < 0)
		tmp = -tmp;
	if (form->justify == 0)
		form->justify = tmp;
	form->is_min = 1;
	if (*format == '*')
		return (format + 1);
	return (format + size);
}

char	*hold_zero(char *format, t_format *form, va_list *arg)
{
	int	tmp;
	int	size;

	tmp = 0;
	size = 0;
	if (*format == '*')
		tmp = va_arg(*arg, int);
	else
		tmp = ft_atoi_size(format, &size);
	if (tmp < 0)
		tmp = -tmp;
	if (form->len == 0)
		form->len = tmp;
	form->is_zero = 1;
	if (*format == '*')
		return (format + 1);
	return (format + size);
}

char	*hold_dot(char *format, t_format *form, va_list *arg)
{
	int tmp;
	int size;

	size = 0;
	tmp = 0;
	if (*format == '*')
		tmp = va_arg(*arg, int);
	else if (*format == '.')
		size = 1;
	else
		tmp = ft_atoi_size(format, &size);
	if (tmp < 0)
		tmp = -tmp;
	if (form->precision == 0)
		form->precision = tmp;
	form->is_dot = 1;
	if (*format == '*')
		return (format + 1);
	return (format + size);
}

char	*hold_width(char *format, t_format *form, va_list *arg)
{
	int tmp;
	int size;

	size = 0;
	if (*format == '*')
		tmp = va_arg(*arg, int);
	else
		tmp = ft_atoi_size(format, &size);
	if (tmp < 0)
	{
		tmp = -tmp;
		form->is_min = 1;
	}
	form->justify = tmp;
	if (*format == '*')
		return (format + 1);
	return (format + size);
}
