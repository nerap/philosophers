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
	long long res;

	res = ((phil->after.tv_usec / 1000) + (phil->after.tv_sec * 1000)) - ((phil->before.tv_usec / 1000) + (phil->before.tv_sec * 1000));
	if (res >= phil->time_to_die)
	{
		if (g_still_eating <= 0)
			return (NULL);
		g_still_eating = 0;
		display("died", phil);
		end();
		return (NULL);
	}	
	return ((void*)phil);
}

void		display(const char *str, t_philo_one *phil)
{
	char		*tr;
	char		*t;
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
}

t_philo_one	*rotate(t_philo_one *phil)
{
	struct timeval	time;

	if (g_still_eating > 0)
	{
		display("is eating", phil);
		usleep(phil->time_to_eat * 1000);
		drop_chopsticks(phil);
	}
	if (phil->is_time && --phil->number_of_time == 0)
	{
		if (--g_still_eating <= 0)
			return (end());
		else
			return (NULL);
	}
	if (g_still_eating > 0)
		display("is sleeping", phil);	
	gettimeofday(&(phil->before), NULL);
	usleep(phil->time_to_sleep * 1000);
	if (g_still_eating > 0 && check_death(phil) == NULL)
		return (NULL);
	//gettimeofday(&(phil->after), NULL);
	if (g_still_eating > 0)
	{
	//	if (check_death(phil) == NULL)
	//		return (NULL);
		if (g_still_eating > 0)
			display("is thinking", phil);
	}
	return (phil);
}
