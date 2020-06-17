/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 06:22:34 by racohen           #+#    #+#             */
/*   Updated: 2019/11/11 06:22:02 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_min_j(t_format *form, char *res)
{
	int		i;
	char	*tmp;

	i = ft_strlen(res) - 1;
	if (form->is_min)
		while (++i < form->justify)
			res = ft_strjoinfree(res, " ");
	else
		while (++i < form->justify)
		{
			tmp = res;
			res = ft_strjoinfree(ft_strdup(" "), res);
			free(tmp);
		}
	return (res);
}

char		*ft_write_s(t_format *form, va_list *arg)
{
	char	*res;
	char	*tmp;

	if ((tmp = va_arg(*arg, char*)) == NULL)
		if ((tmp = ft_strdup("(null)")) == NULL)
			return (NULL);
	if (form->is_dot)
	{
		if ((res = ft_substr(tmp, 0, form->precision)) == NULL)
			return (NULL);
	}
	else if ((res = ft_substr(tmp, 0, ft_strlen(tmp))) == NULL)
		return (NULL);
	if ((res = ft_min_j(form, res)) == NULL)
		return (NULL);
	form->width += ft_strlen(res);
	return (res);
}
