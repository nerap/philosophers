/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:15:30 by racohen           #+#    #+#             */
/*   Updated: 2019/11/09 14:05:01 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_len(const char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

static char	*ft_cat(char *dest, const char *src)
{
	int i;
	int len;

	i = 0;
	len = ft_len(dest);
	while (src[i])
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}

static char	*ft_cpy(char *dest, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strjoinfree(char const *s1, char const *s2)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((str = malloc(ft_len(s1) + ft_len(s2) + 1)) == NULL)
		return (NULL);
	ft_cpy(str, s1);
	ft_cat(str, s2);
	free((char*)s1);
	return (str);
}
