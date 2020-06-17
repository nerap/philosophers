/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 22:39:51 by racohen           #+#    #+#             */
/*   Updated: 2019/11/27 16:58:28 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo_two.h"

void		drop_chopsticks(void)
{
	sem_wait(g_sem.sem);
	g_sem.value += 2;
	sem_post(g_sem.sem);
}

int			grab_chopsticks(t_philo_two *phil)
{
	if (g_still_eating > 0)
	{
		if (g_sem.value > 1)
		{
			sem_wait(g_sem.sem);
			g_sem.value -= 2;
			sem_post(g_sem.sem);
		}
		else
			return (-1);
		if (g_still_eating > 0)
			display("has taken fork", phil);
		else
		{
			drop_chopsticks();
			end(phil);
			return (-1);
		}
		return (0);
	}
	end(phil);
	return (-1);
}

void		*thread_run(void *philo_two)
{
	struct timeval	time;
	t_philo_two		*phil;

	phil = (t_philo_two*)philo_two;
	gettimeofday(&(phil->before), NULL);
	while (g_still_eating > 0)
	{
		gettimeofday(&(phil->after), NULL);
		if (!phil->is_time &&
			phil->after.tv_usec - phil->before.tv_usec >= phil->time_to_die)
		{
			display("died", phil);
			return (end(phil));
		}
		if (phil->is_time && phil->number_of_time <= 0)
		{
			pthread_detach(phil->phil);
			return (NULL);
		}
		else if (g_still_eating >= 0 && grab_chopsticks(phil) == 0)
			if ((phil = rotate(phil)) == NULL)
				return (NULL);
	}
	return (end(phil));
}

t_philo_two	*init(t_philo_two *philo_two, int ac, char *const av[])
{
	int	nb_phil;
	int	i;

	i = -1;
	nb_phil = ft_atol(av[1]);
	if ((philo_two = malloc(sizeof(t_philo_two) * nb_phil)) == NULL)
		return (NULL);
	while (++i < nb_phil)
	{
		philo_two[i].id = i + 1;
		philo_two[i].number_of_philosopher = nb_phil;
		philo_two[i].time_to_die = ft_atol(av[2]);
		philo_two[i].time_to_eat = ft_atol(av[3]);
		philo_two[i].time_to_sleep = ft_atol(av[4]);
		if (ac > 5 + nb_phil - 1)
		{
			philo_two[i].number_of_time = ft_atol(av[5 + i]);
			philo_two[i].is_time = 1;
		}
		else
			philo_two[i].is_time = 0;
	}
	return (philo_two);
}

int			main(int ac, char *const av[])
{
	int			i;
	t_philo_two	*philo_two;

	i = 0;
	if ((philo_two = init(philo_two, ac, av)) == NULL)
		return (-1);
	g_still_eating = philo_two[0].number_of_philosopher;
	sem_unlink(SEM_NAME);
	g_sem.value = g_still_eating;
	if ((g_sem.sem = sem_open(SEM_NAME, O_CREAT, 0644, g_still_eating / 2))
		== SEM_FAILED)
		return (-1);
	while (i < philo_two[i].number_of_philosopher)
	{
		if (pthread_create(&philo_two[i].phil, NULL, thread_run, &philo_two[i]))
			return (-1);
		i++;
	}
	while (g_still_eating > 0)
		(void)ac;
	sem_close(g_sem.sem);
	free(philo_two);
	return (0);
}
