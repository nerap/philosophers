/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 10:07:15 by racohen           #+#    #+#             */
/*   Updated: 2019/11/11 06:22:36 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_u_prec(t_format *form, char *res)
{
	int		i;
	char	*tmp;

	i = ft_strlen(res) - 1;
	if (form->is_dot)
	{
		while (++i < form->precision)
		{
			tmp = res;
			res = ft_strjoinfree(ft_strdup("0"), res);
			free(tmp);
		}
	}
	else if (form->is_zero)
		while (++i < (int)form->len)
		{
			tmp = res;
			res = ft_strjoinfree(ft_strdup("0"), res);
			free(tmp);
		}
	return (res);
}

char	*ft_min_ju(t_format *form, char *res)
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

char	*ft_write_u(t_format *form, va_list *arg)
{
	unsigned int	temp;
	char			*res;

	temp = va_arg(*arg, unsigned int);
	if (temp == 0 && form->is_dot && form->precision == 0)
	{
		if ((res = ft_strdup("")) == NULL)
			return (NULL);
	}
	else if ((res = ft_itoa_u(temp)) == NULL)
		return (NULL);
	if (form->is_min && form->is_zero)
		form->is_zero = 0;
	if ((res = ft_u_prec(form, res)) == NULL)
		return (NULL);
	if ((res = ft_min_ju(form, res)) == NULL)
		return (NULL);
	form->width += ft_strlen(res);
	return (res);
}
