/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 03:40:33 by racohen           #+#    #+#             */
/*   Updated: 2019/11/25 10:09:54 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo_two.h"

void		*end(t_philo_two *phil)
{
	pthread_detach(phil->phil);
	g_still_eating = 0;
	sem_unlink(SEM_NAME);
	sem_close(g_sem.sem);
	return (NULL);
}

void		display(const char *str, t_philo_two *phil)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	ft_printf("%d %d %s\n", phil->id, time.tv_usec / 1000, str);
}

t_philo_two	*rotate(t_philo_two *phil)
{
	struct timeval	time;

	if (g_still_eating <= 0)
		return (end(phil));
	display("is eating", phil);
	usleep(phil->time_to_eat);
	if (phil->is_time && --phil->number_of_time == 0)
		g_still_eating--;
	drop_chopsticks();
	if (g_still_eating <= 0)
		return (end(phil));
	display("is sleeping", phil);
	usleep(phil->time_to_sleep);
	gettimeofday(&(phil->before), NULL);
	if (g_still_eating <= 0)
		return (end(phil));
	display("is thinking", phil);
	return (phil);
}
