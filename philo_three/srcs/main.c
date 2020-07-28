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

#include "../includes/ft_philo_three.h"

int			grab_chopsticks(t_philo_three *phil)
{
	sem_wait(g_sem_eat);
	phil->is_eating = 1;
	sem_wait(g_sem);
	sem_wait(g_sem_write);
	display("has taken fork", phil);
	sem_post(g_sem_write);
	sem_wait(g_sem);
	sem_wait(g_sem_write);
	display("has taken fork", phil);
	sem_post(g_sem_write);
	return (0);
}

void		*thread_run(void *philo_three)
{
	struct timeval		time;
	t_philo_three		*phil;

	phil = (t_philo_three*)philo_three;
	phil->is_eating = 0;
	gettimeofday(&(phil->before), NULL);
	gettimeofday(&(phil->after), NULL);
	while (1)
	{
		sem_wait(g_sem_done);
		sem_post(g_sem_done);
		if ((phil->is_time && phil->number_of_time <= 0))
			break ;
		else if (grab_chopsticks(phil) == 0)
		{
			if ((phil = rotate(phil)) == NULL)
				break ;
		}
	}
	return (NULL);
}

void		init(int ac, char *const av[])
{
	int	i;

	i = -1;
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_DIE);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DONE);
	sem_unlink(SEM_EAT);
	g_all.number_of_philosopher = ft_atol(av[1]);
	g_all.time_to_die = ft_atol(av[2]);
	g_all.time_to_eat = ft_atol(av[3]);
	g_all.time_to_sleep = ft_atol(av[4]);
	gettimeofday(&(g_all.before), NULL);
	gettimeofday(&(g_all.after), NULL);
	g_all.is_time = 0;
	if (ac > 5)
	{
		g_all.number_of_time = ft_atol(av[5]);
		g_all.is_time = 1;
	}
	return ;
}

int			init_sem(int ac, char *const av[])
{
	if (!check_param(ac, av))
		return (0);
	init(ac, av);
	if ((g_sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, ft_atol(av[1])))
		== SEM_FAILED)
		return (0);
	if ((g_sem_die = sem_open(SEM_DIE, O_CREAT | O_EXCL, 0644, 1))
		== SEM_FAILED)
		return (0);
	if ((g_sem_write = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0644, 1))
		== SEM_FAILED)
		return (0);
	if ((g_sem_done = sem_open(SEM_DONE, O_CREAT | O_EXCL, 0644, 1))
		== SEM_FAILED)
		return (0);
	if ((g_sem_eat = sem_open(SEM_EAT, O_CREAT | O_EXCL, 0644,
		ft_atol(av[1]) / 2)) == SEM_FAILED)
		return (0);
	usleep(2000);
	return (g_all.number_of_philosopher);
}

int			main(int ac, char *const av[])
{
	int			i;
	int			nb;
	pid_t		p;

	i = -1;
	if ((nb = init_sem(ac, av)) == 0)
		return (0);
	while (++i < nb)
	{
		g_all.id = i + 1;
		p = fork();
		if (p != 0)
			continue ;
		else if (pthread_create(&g_all.phil, NULL, thread_run, &g_all))
			return (-1);
		break ;
	}
	if (p != 0)
		waitpid(-1, NULL, 0);
	else
		while (1)
			check_alive(nb);
	if (p != 0)
		end();
	return (0);
}
