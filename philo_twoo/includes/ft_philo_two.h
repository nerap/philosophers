/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_two.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 22:35:59 by racohen           #+#    #+#             */
/*   Updated: 2020/07/02 09:31:42 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_TWO_H
# define FT_PHILO_TWO_H
# define _GNU_SOURCE
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# ifndef SEM_NAME
#  define SEM_NAME "SEM"
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
	int				is_eating;
	int				is_time;
	struct timeval	before;
	struct timeval	after;
}					t_philo_two;

t_philo_two			*g_all;
int					g_still_eating;
sem_t				*g_sem;

long				ft_atol(const char *str);
int					check_param(int ac, char *const av[]);
void				*end();
void				*check_alive(int nb);
void				display(const char *str, t_philo_two *phil);
t_philo_two			*rotate(t_philo_two *phil);
int					is_alpha(const char *str);
char				*ft_strjoinfreeboth(char *s1, char *s2,
				int lens1, int lens2);
char				*ft_strdup(const char *src);
void				*check_death(t_philo_two *phil);
char				*ft_itoa(int n);
size_t				ft_strlen(const char *s);

#endif
