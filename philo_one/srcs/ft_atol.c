/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 15:26:56 by racohen           #+#    #+#             */
/*   Updated: 2019/11/24 23:00:42 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo_one.h"

int			is_alpha(const char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

void		*check_alive(int nb)
{
	int	i;

	usleep(1);
	i = -1;
	while (++i < nb)
	{
		if (check_death(&g_all[i]) == NULL)
			return (NULL);
		gettimeofday(&(g_all[i].after), NULL);
	}
	return (&g_all[0]);
}

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

long		ft_atol(const char *str)
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
			res = (res * 10) + str[i] - 48;
		i++;
	}
	return (res * is_neg);
}

int			check_param(int ac, char *const av[])
{
	int			i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		write(1, "Wrong number of arguments\n", 26);
		return (0);
	}
	while (i < ac)
		if (is_alpha(av[i++]) == 0)
		{
			write(1, "Non numeric parameters\n", 23);
			return (0);
		}
	if (ft_atol(av[1]) < 2 || ft_atol(av[2]) < 61 ||
		ft_atol(av[3]) < 61 || ft_atol(av[4]) < 61)
	{
		write(1, "Value of the parameters too low\n", 32);
		return (0);
	}
	return (1);
}
