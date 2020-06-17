/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 10:23:34 by racohen           #+#    #+#             */
/*   Updated: 2019/11/09 10:23:42 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_len(unsigned int nbr)
{
	int len;

	len = 0;
	len = (nbr <= 0 ? 1 : 0);
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa_u(unsigned int n)
{
	unsigned int	nbr;
	int				sign;
	int				len;
	char			*alpha;

	sign = (n < 0 ? 1 : 0);
	alpha = NULL;
	len = ft_len(n);
	nbr = (n < 0 ? -n : n);
	if ((alpha = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	alpha[len--] = '\0';
	while (len >= 0)
	{
		alpha[len] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	if (sign == 1)
		alpha[0] = '-';
	return (alpha);
}
