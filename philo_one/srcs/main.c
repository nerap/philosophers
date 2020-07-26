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
	gettimeofday(&(phil->before), NULL);
	gettimeofday(&(phil->after), NULL);
	while (1)
	{
		//gettimeofday(&(phil->after), NULL);
		//check_death(phil);
		if ((phil->is_time && phil->number_of_time <= 0) || g_still_eating <= 0)
			break;
		else if (g_still_eating > 0 && grab_chopsticks(phil) == 0)
		{
			if ((phil = rotate(phil)) == NULL)
				break;
		}
		else
			break;
	}
	return (NULL);
}

t_philo_one	*init(int ac, char *const av[])
{
	int	nb_phil;
	int	i;

	i = -1;
	nb_phil = ft_atol(av[1]);
	g_still_eating = nb_phil;
	if ((g_all = malloc(sizeof(t_philo_one) * nb_phil)) == NULL)
		return (NULL);
	if ((g_chops = malloc(sizeof(pthread_mutex_t) * (nb_phil))) == NULL)
		return (NULL);
	while (++i < nb_phil)
	{
		g_all[i].id = i + 1;
		g_all[i].number_of_philosopher = nb_phil;
		g_all[i].time_to_die = ft_atol(av[2]);
		g_all[i].time_to_eat = ft_atol(av[3]);
		g_all[i].time_to_sleep = ft_atol(av[4]);
		gettimeofday(&(g_all[i].before), NULL);
		gettimeofday(&(g_all[i].after), NULL);
		if (ac > 5)
		{
			g_all[i].number_of_time = ft_atol(av[5]);
			g_all[i].is_time = 1;
		}
		else
			g_all[i].is_time = 0;
	}
	return (g_all);
}

int			main(int ac, char *const av[])
{
	int			i;
	int			nb;

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
	i = 0;
	if ((g_all = init(ac, av)) == NULL)
		return (0);
	nb = g_all[i].number_of_philosopher;
	while (i < nb)
		if (pthread_mutex_init(&g_chops[i++], NULL) == -1)
			return (-1);
	i = 0;
	while (i < nb)
	{
		if (pthread_create(&g_all[i].phil, NULL, thread_run, &g_all[i]))
			return (-1);
		i++;
	}
	while (g_still_eating > 0)
	{
		usleep(1);
		i = -1;
		while (++i < nb)
		{
			if (check_death(&g_all[i]) == NULL)
				break;
			gettimeofday(&(g_all[i].after), NULL);
		}
	}
	return (0);
}
