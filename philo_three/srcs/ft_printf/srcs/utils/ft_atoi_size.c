/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 15:26:56 by racohen           #+#    #+#             */
/*   Updated: 2019/11/09 09:54:31 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	check_sign(const char *str, int i, int *is_neg)
{
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*is_neg = -1;
		i++;
	}
	return (i);
}

int			ft_atoi_size(const char *str, int *size)
{
	int			i;
	int			is_neg;
	long long	res;

	i = 0;
	is_neg = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	i = check_sign(str, i, &is_neg);
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			break ;
		else
		{
			res = (res * 10) + str[i] - 48;
			*size = *size + 1;
		}
		i++;
	}
	return (res * is_neg);
}
