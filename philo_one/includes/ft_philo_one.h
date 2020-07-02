/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_one.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 22:35:59 by racohen           #+#    #+#             */
/*   Updated: 2020/07/02 09:31:42 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_ONE_H
# define FT_PHILO_ONE_H

# include "../srcs/ft_printf/includes/ft_printf.h"
# include <libc.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_philo_one
{
	int				id;
	pthread_t		phil;
	long			number_of_philosopher;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_time;
	int				is_time;
	struct timeval	before;
	struct timeval	after;
}					t_philo_one;

t_philo_one			*g_all;
int					g_still_eating;
pthread_mutex_t		*g_chops;

long				ft_atol(const char *str);
void				mutex_destroy(long number);
void				*end();
void				display(const char *str, t_philo_one *phil);
t_philo_one			*rotate(t_philo_one *phil);
void				drop_chopsticks(t_philo_one *phil);
void				*check_death(t_philo_one *phil);

#endif
