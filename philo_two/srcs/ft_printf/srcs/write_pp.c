/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_pp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 05:11:38 by racohen           #+#    #+#             */
/*   Updated: 2019/11/12 00:26:12 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_is_zero(t_format *form, char *res)
{
	int		i;
	char	*tmp;

	i = ft_strlen(res) - 1;
	if (form->is_zero)
		while (++i < (int)form->len)
		{
			tmp = res;
			res = ft_strjoinfree(ft_strdup(" "), res);
			free(tmp);
		}
	return (res);
}

char	*ft_min_just(t_format *form, char *res)
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
	if ((res = ft_is_zero(form, res)) == NULL)
		return (NULL);
	return (res);
}
