/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:51:15 by racohen           #+#    #+#             */
/*   Updated: 2019/11/08 07:06:40 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*temp;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((size_t)start > len)
	{
		if ((temp = malloc(1)) == NULL)
			return (NULL);
		temp[0] = '\0';
		return (temp);
	}
	if ((temp = malloc((len + 1) * sizeof(char))) == NULL)
		return (NULL);
	temp[len] = '\0';
	while (len--)
	{
		temp[i] = s[start];
		i++;
		start++;
	}
	return (temp);
}
