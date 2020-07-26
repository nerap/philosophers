/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:15:30 by racohen           #+#    #+#             */
/*   Updated: 2019/11/11 19:11:35 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo_one.h"

static char	*ft_cat(char *dest, const char *src, int lens1, int lens2)
{
	int i;

	i = 0;
	while (i < lens2)
	{
		dest[lens1 + i] = src[i];
		i++;
	}
	dest[lens1 + i] = '\0';
	return (dest);
}

static char	*ft_cpy(char *dest, const char *src, int lens1)
{
	int i;

	i = 0;
	while (i < lens1)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char		*ft_strjoinfreeboth(char *s1, char *s2, int lens1, int lens2)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((str = malloc(lens1 + lens2 + 1)) == NULL)
		return (NULL);
	ft_cpy(str, s1, lens1);
	ft_cat(str, s2, lens1, lens2);
	free(s1);
	free(s2);
	return (str);
}
