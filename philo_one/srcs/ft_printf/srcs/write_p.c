/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 06:22:46 by racohen           #+#    #+#             */
/*   Updated: 2019/11/12 21:35:54 by racohen          ###   ########.fr       */
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

char		*add_zero(int i, t_format *form, char *res)
{
	char	*tmp;
	char	*tmp2;

	while (++i < form->precision + 2)
	{
		tmp = ft_substr(res, 2, ft_strlen(res));
		tmp2 = ft_strjoinfree(ft_strdup("0"), tmp);
		if ((res = ft_strjoinfreeboth(ft_strdup("0x"),
			tmp2, 2, ft_strlen(tmp2))) == NULL)
		{
			free(tmp);
			free(tmp2);
			return (NULL);
		}
	}
	return (res);
}

char		*ft_convert_addr(void *ptr)
{
	uintmax_t			ads;
	char				*res;
	char				*hex;
	char				*tab;

	hex = "0123456789abcdef";
	ads = (uintmax_t)ptr;
	if ((res = ft_strdup("0x")) == NULL)
		return (NULL);
	if ((tab = ft_strdup("")) == NULL)
		return (NULL);
	while (ads > 0)
	{
		if ((tab = ft_concat_char(tab, hex[ads % 16])) == NULL)
			return (NULL);
		ads /= 16;
	}
	return (ft_strjoinfree(res, (char*)tab));
}

char		*ft_p_precision(va_list *arg)
{
	void	*tmp;
	char	*res;

	if ((tmp = va_arg(*arg, void*)) == NULL)
	{
		if ((res = ft_strdup("0x0")) == NULL)
			return (NULL);
	}
	else if ((res = ft_convert_addr(tmp)) == NULL)
		return (NULL);
	return (res);
}

char		*ft_write_p(t_format *form, va_list *arg)
{
	int		i;
	char	*res;

	if ((res = ft_p_precision(arg)) == NULL)
		return (NULL);
	i = ft_strlen(res) - 1;
	if (form->is_zero && form->is_dot == 0 && form->is_min == 0)
	{
		form->is_zero = 0;
		form->is_dot = 1;
		form->precision = form->justify - 2;
	}
	if (form->is_dot && i < form->precision + 2)
	{
		if ((res = add_zero(i, form, res)) == NULL)
			return (NULL);
	}
	if ((res = ft_min_just(form, res)) == NULL)
		return (NULL);
	form->width += ft_strlen(res);
	return (res);
}
