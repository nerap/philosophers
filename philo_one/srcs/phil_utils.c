/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 03:40:33 by racohen           #+#    #+#             */
/*   Updated: 2020/06/17 10:28:42 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo_one.h"

void		mutex_destroy(long number)
{
	int i;

	i = -1;
	while (!g_chops && ++i < number)
		pthread_mutex_destroy(&g_chops[i]);
	if (!g_chops)
		free(g_chops);
}

void		*end()
{
	int i;

	i = -1;
	mutex_destroy(g_all[0].number_of_philosopher);
	if (!g_all)
		free(g_all);
	return (NULL);
}

void		*check_death(t_philo_one *phil)
{
	if (phil->after.tv_usec - phil->before.tv_usec >= phil->time_to_die)
	{
		g_still_eating = 0;
		display("died", phil);
		end();
	}	
	return (NULL);
}

void		display(const char *str, t_philo_one *phil)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	ft_printf("%d %d %s\n", phil->id, time.tv_usec / 1000, str);
}

t_philo_one	*rotate(t_philo_one *phil)
{
	struct timeval	time;

	
	if (g_still_eating <= 0)
		return NULL;
	display("is eating", phil);
	usleep(phil->time_to_eat);
	gettimeofday(&(phil->before), NULL);
	if (phil->is_time && --phil->number_of_time == 0)
	{
		if (--g_still_eating <= 0)
		{
			g_still_eating = 0;
			mutex_destroy(g_all[0].number_of_philosopher);
    			free(g_all);
		}
		drop_chopsticks(phil);	
		if (g_still_eating > 0)
		{
			display("is sleeping", phil);
			usleep(phil->time_to_sleep);
		}
		else
			return NULL;
		gettimeofday(&(phil->after), NULL);
		check_death(phil);
		display("is thinking", phil);
	}
	return (phil);
}
