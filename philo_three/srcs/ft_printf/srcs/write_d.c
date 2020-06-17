/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 06:23:02 by racohen           #+#    #+#             */
/*   Updated: 2019/11/11 19:44:34 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_i_prec(t_format *form, char *res)
{
	int		i;
	char	*tmp;

	i = ft_strlen(res) - 1;
	if (form->is_zero && form->is_min == 0 &&
		form->is_dot == 0 && form->len == 0)
		form->len = form->justify;
	while (++i < (int)form->len)
	{
		tmp = res;
		res = ft_strjoinfree(ft_strdup("0"), res);
		free(tmp);
		if (res[1] == '-')
		{
			res[0] = '-';
			res[1] = '0';
		}
	}
	return (res);
}

char	*ft_d_prec(t_format *form, char *res)
{
	int		i;
	char	*tmp;

	i = ft_strlen(res) - 1;
	if (form->is_dot)
	{
		if (res[0] == '-' && i + 1 < form->precision)
			form->precision += 1;
		while (++i < form->precision)
		{
			tmp = res;
			res = ft_strjoinfree(ft_strdup("0"), res);
			free(tmp);
			if (res[1] == '-')
			{
				res[0] = '-';
				res[1] = '0';
			}
		}
	}
	else if (form->is_zero)
		if ((res = ft_i_prec(form, res)) == NULL)
			return (NULL);
	return (res);
}

char	*ft_min_jus(t_format *form, char *res)
{
	int		i;
	char	*tmp;

	i = ft_strlen(res) - 1;
	if (form->is_min)
		while (++i < form->justify)
			res = ft_strjoinfree(res, " ");
	else
		while ((++i < form->justify && form->is_zero == 0) ||
				(i < (int)form->len && form->is_zero == 1))
		{
			tmp = res;
			res = ft_strjoinfree(ft_strdup(" "), res);
			free(tmp);
		}
	return (res);
}

char	*ft_write_d(t_format *form, va_list *arg)
{
	int		temp;
	char	*res;

	temp = va_arg(*arg, int);
	if (temp == 0 && form->is_dot && form->precision == 0)
	{
		if ((res = ft_strdup("")) == NULL)
			return (NULL);
	}
	else if ((res = ft_itoa(temp)) == NULL)
		return (NULL);
	if (form->is_min && form->is_zero)
		form->is_zero = 0;
	if ((res = ft_d_prec(form, res)) == NULL)
		return (NULL);
	if ((res = ft_min_jus(form, res)) == NULL)
		return (NULL);
	form->width += ft_strlen(res);
	return (res);
}
