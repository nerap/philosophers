/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 04:26:16 by racohen           #+#    #+#             */
/*   Updated: 2019/11/25 05:31:39 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list list;
	char	*res;
	int		resultat;
	int		size;

	resultat = 0;
	size = 0;
	if (format == NULL)
		return (resultat);
	if ((res = ft_strdup("")) == NULL)
		return (0);
	va_start(list, format);
	if ((res = parse_format(&list, (char*)format, &size, res)) == NULL)
		return (0);
	write(1, res, size);
	resultat = size;
	free(res);
	va_end(list);
	return (resultat);
}
