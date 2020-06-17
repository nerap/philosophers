/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 06:24:07 by racohen           #+#    #+#             */
/*   Updated: 2019/11/11 05:48:57 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_concat_char(char *str, char c)
{
	int		len;
	char	*tmp;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if ((tmp = (char*)malloc(len + 2)) == NULL)
		return (NULL);
	ft_memcpy(tmp + 1, str, len);
	tmp[len + 1] = '\0';
	tmp[0] = c;
	free(str);
	return (tmp);
}

static char	*ft_convert_addr(unsigned int nb, t_format *form)
{
	char	*res;
	char	*hex;

	if (form->type == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if ((res = ft_strdup("")) == NULL)
		return (NULL);
	if (nb == 0)
		if ((res = ft_concat_char(res, '0')) == NULL)
			return (NULL);
	while (nb > 0)
	{
		if ((res = ft_concat_char(res, hex[nb % 16])) == NULL)
			return (NULL);
		nb /= 16;
	}
	return (res);
}

static char	*ft_x_precision(unsigned int nb, t_format *form)
{
	int				i;
	char			*tmp;
	char			*res;

	if (form->is_min && form->is_zero)
		form->is_zero = 0;
	if ((res = ft_convert_addr(nb, form)) == NULL)
		return (NULL);
	i = ft_strlen(res) - 1;
	if (form->is_dot)
		while (++i < form->precision)
		{
			tmp = res;
			res = ft_strjoinfree(ft_strdup("0"), res);
			free(tmp);
		}
	if (form->is_dot == 0 && form->is_zero)
		while (++i < (int)form->len)
		{
			tmp = res;
			res = ft_strjoinfree(ft_strdup("0"), res);
			free(tmp);
		}
	return (res);
}

char		*ft_write_x(t_format *form, va_list *arg)
{
	char			*res;
	char			*tmp;
	unsigned int	i;

	res = NULL;
	i = va_arg(*arg, unsigned int);
	if (i == 0 && form->is_dot && form->precision == 0)
		if ((res = ft_strdup("")) == NULL)
			return (NULL);
	if (res == NULL && (res = ft_x_precision(i, form)) == NULL)
		return (NULL);
	i = ft_strlen(res) - 1;
	if (form->is_min)
		while (++i < (unsigned int)form->justify)
			res = ft_strjoinfree(res, " ");
	else
		while ((++i < (unsigned int)form->justify && form->is_zero == 0) ||
				(i < (unsigned int)form->len && form->is_zero == 1))
		{
			tmp = res;
			res = ft_strjoinfree(ft_strdup(" "), res);
			free(tmp);
		}
	form->width += ft_strlen(res);
	return (res);
}
