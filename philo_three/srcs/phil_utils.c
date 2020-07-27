/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 03:40:33 by racohen           #+#    #+#             */
/*   Updated: 2020/07/02 09:55:43 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo_three.h"

void			end(void)
{
	sem_close(g_sem);
	sem_close(g_sem_eat);
	sem_close(g_sem_die);
	sem_close(g_sem_write);
	sem_close(g_sem_done);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_DIE);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DONE);
	return ;
}

void			*check_death(t_philo_three *phil)
{
	long long res;

	res = ((phil->after.tv_usec / 1000) + (phil->after.tv_sec * 1000))
		- ((phil->before.tv_usec / 1000) + (phil->before.tv_sec * 1000));
	if (res >= phil->time_to_die)
	{
		sem_wait(g_sem_die);
		sem_wait(g_sem_done);
		sem_wait(g_sem_write);
		display("died", phil);
		return (NULL);
	}
	else if (phil->is_time && phil->number_of_time <= 0)
		return (NULL);
	return ((void*)phil);
}

void			display(const char *str, t_philo_three *phil)
{
	char			*tr;
	char			*t;
	struct timeval	time;

	gettimeofday(&time, NULL);
	t = ft_itoa(time.tv_usec / 1000);
	tr = ft_strjoinfreeboth(t, ft_strdup(" "), ft_strlen(t), 1);
	t = ft_itoa(phil->id);
	tr = ft_strjoinfreeboth(tr, t, ft_strlen(tr), ft_strlen(t));
	tr = ft_strjoinfreeboth(tr, ft_strdup(" "), ft_strlen(tr), 1);
	tr = ft_strjoinfreeboth(tr, ft_strdup(str), ft_strlen(tr), ft_strlen(str));
	tr = ft_strjoinfreeboth(tr, ft_strdup("\n"), ft_strlen(tr), 1);
	write(1, tr, ft_strlen(tr));
	free(tr);
}

t_philo_three	*rotate(t_philo_three *phil)
{
	struct timeval	time;

	sem_wait(g_sem_write);
	display("is eating", phil);
	sem_post(g_sem_write);
	sem_post(g_sem_eat);
	gettimeofday(&(phil->before), NULL);
	phil->is_eating = 0;
	usleep(phil->time_to_eat * 1000);
	gettimeofday(&(phil->after), NULL);
	sem_post(g_sem);
	sem_post(g_sem);
	if (phil->is_time && --phil->number_of_time <= 0)
		return (NULL);
	sem_wait(g_sem_write);
	display("is sleeping", phil);
	sem_post(g_sem_write);
	usleep(phil->time_to_sleep * 1000);
	gettimeofday(&(phil->after), NULL);
	sem_wait(g_sem_write);
	display("is thinking", phil);
	sem_post(g_sem_write);
	return (phil);
}
