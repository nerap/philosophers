/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 19:09:46 by racohen           #+#    #+#             */
/*   Updated: 2019/11/08 02:15:56 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*ptr;

	i = 0;
	len = ft_strlen(src);
	if ((ptr = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
