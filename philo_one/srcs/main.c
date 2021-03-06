/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 22:39:51 by racohen           #+#    #+#             */
/*   Updated: 2020/07/02 10:35:39 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo_one.h"

void		drop_chopsticks(t_philo_one *phil)
{
	int	left_chops;
	int	right_chops;

	left_chops = phil->id - 1;
	right_chops = (phil->id) % phil->number_of_philosopher;
	pthread_mutex_unlock(&g_chops[right_chops]);
	pthread_mutex_unlock(&g_chops[left_chops]);
}

int			grab_chopsticks(t_philo_one *phil)
{
	int	left_chops;
	int	right_chops;

	left_chops = phil->id - 1;
	right_chops = (phil->id) % phil->number_of_philosopher;
	if (g_all[left_chops].is_eating || g_all[right_chops].is_eating)
		return (-1);
	phil->is_eating = 1;
	if (g_chops == NULL)
		return (-1);
	pthread_mutex_lock(&g_chops[left_chops]);
	if (g_still_eating > 0)
		display("has taken fork", phil);
	else
		return (-1);
	if (g_chops == NULL)
		return (-1);
	pthread_mutex_lock(&g_chops[right_chops]);
	if (g_still_eating > 0)
		display("has taken fork", phil);
	else
		return (-1);
	return (0);
}

void		*thread_run(void *philo_one)
{
	struct timeval	time;
	t_philo_one		*phil;

	phil = (t_philo_one*)philo_one;
	phil->is_eating = 0;
	gettimeofday(&(phil->before), NULL);
	gettimeofday(&(phil->after), NULL);
	while (1)
	{
		if ((phil->is_time && phil->number_of_time <= 0) || g_still_eating <= 0)
			break ;
		else if (g_still_eating > 0 && grab_chopsticks(phil) == 0)
		{
			if ((phil = rotate(phil)) == NULL)
				break ;
		}
	}
	return (NULL);
}

t_philo_one	*init(int ac, char *const av[])
{
	int	i;

	i = -1;
	g_still_eating = ft_atol(av[1]);
	if ((g_all = malloc(sizeof(t_philo_one) * ft_atol(av[1]))) == NULL)
		return (NULL);
	if ((g_chops = malloc(sizeof(pthread_mutex_t) * ft_atol(av[1]))) == NULL)
		return (NULL);
	while (++i < ft_atol(av[1]))
	{
		g_all[i].id = i + 1;
		g_all[i].number_of_philosopher = ft_atol(av[1]);
		g_all[i].time_to_die = ft_atol(av[2]);
		g_all[i].time_to_eat = ft_atol(av[3]);
		g_all[i].time_to_sleep = ft_atol(av[4]);
		gettimeofday(&(g_all[i].before), NULL);
		gettimeofday(&(g_all[i].after), NULL);
		g_all[i].is_time = 0;
		if (ac > 5)
		{
			g_all[i].number_of_time = ft_atol(av[5]);
			g_all[i].is_time = 1;
		}
	}
	return (g_all);
}

int			main(int ac, char *const av[])
{
	int			i;
	int			nb;

	if (!check_param(ac, av))
		return (0);
	i = -1;
	if ((g_all = init(ac, av)) == NULL)
		return (0);
	nb = g_all[0].number_of_philosopher;
	while (++i < nb)
		pthread_mutex_init(&g_chops[i], NULL);
	i = -1;
	while (++i < nb)
		if (pthread_create(&g_all[i].phil, NULL, thread_run, &g_all[i]))
			return (-1);
	usleep(1000);
	while (1)
		if (check_alive(nb) == NULL)
			break ;
	return (0);
}
