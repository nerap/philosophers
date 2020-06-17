/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 06:14:08 by racohen           #+#    #+#             */
/*   Updated: 2019/11/11 21:32:31 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_write_c(t_format *form, va_list *arg)
{
	int		i;
	char	*res;

	i = 0;
	if ((res = (char*)malloc(sizeof(char) * 2)) == NULL)
		return (NULL);
	res[0] = va_arg(*arg, int);
	res[1] = '\0';
	if (form->is_min)
		while (++i < form->justify)
			res = ft_strjoinfreeboth(res, ft_strdup(" "), i, 1);
	else
		while (++i < form->justify)
			res = ft_strjoinfreeboth(ft_strdup(" "), res, 1, i);
	if (form->justify != 0)
		form->width += form->justify;
	else
		form->width += 1;
	return (res);
}
