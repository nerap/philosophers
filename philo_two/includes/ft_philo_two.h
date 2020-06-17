/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_two.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:10:42 by racohen           #+#    #+#             */
/*   Updated: 2019/11/25 10:12:35 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_TWO_H
# define FT_PHILO_TWO_H

# include "../srcs/ft_printf/includes/ft_printf.h"
# include <libc.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# ifndef SEM_NAME
#  define SEM_NAME "/s"
# endif

typedef struct		s_philo_two
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
}					t_philo_two;

typedef struct		s_sem
{
	int				value;
	sem_t			*sem;
}					t_sem;

int					g_still_eating;
t_sem				g_sem;

long				ft_atol(const char *str);
void				*end(t_philo_two *phil);
void				display(const char *str, t_philo_two *phil);
t_philo_two			*rotate(t_philo_two *phil);
void				drop_chopsticks();

#endif
