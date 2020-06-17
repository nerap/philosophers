/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 06:14:08 by racohen           #+#    #+#             */
/*   Updated: 2019/11/11 06:20:48 by racohen          ###   ########.fr       */
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
	return (tmp);
}

char		*ft_pr_prec(t_format *form, char *res)
{
	int		i;
	char	*tmp;

	i = 0;
	if (form->is_zero)
		while (++i < (int)form->len)
		{
			tmp = res;
			res = ft_strjoinfree(ft_strdup("0"), res);
			free(tmp);
		}
	return (res);
}

char		*ft_write_pr(t_format *form, va_list *arg)
{
	int		i;
	char	*res;
	char	*tmp;

	(void)arg;
	if ((res = ft_concat_char("", form->type)) == NULL)
		return (NULL);
	if (form->is_min && form->is_zero)
		form->is_zero = 0;
	i = 0;
	if ((res = ft_pr_prec(form, res)) == NULL)
		return (NULL);
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
	form->width += ft_strlen(res);
	return (res);
}
