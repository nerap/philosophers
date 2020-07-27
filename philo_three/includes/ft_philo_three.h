/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_three.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 22:35:59 by racohen           #+#    #+#             */
/*   Updated: 2020/07/02 09:31:42 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_THREE_H
# define FT_PHILO_THREE_H
# define _GNU_SOURCE
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# ifndef SEM_NAME
#  define SEM_NAME "SEM"
# endif
# ifndef SEM_DIE
#  define SEM_DIE "DIE"
# endif
# ifndef SEM_WRITE
#  define SEM_WRITE "WRITE"
# endif
# ifndef SEM_DONE
#  define SEM_DONE "DONE"
# endif
# ifndef SEM_EAT
#  define SEM_EAT "EAT"
# endif


typedef struct		s_philo_three
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
}					t_philo_three;

t_philo_three		g_all;
sem_t				*g_sem;
sem_t				*g_sem_done;
sem_t				*g_sem_die;
sem_t				*g_sem_write;
sem_t				*g_sem_eat;

long				ft_atol(const char *str);
int					check_param(int ac, char *const av[]);
void				end();
void				check_alive(int nb);
void				display(const char *str, t_philo_three *phil);
t_philo_three		*rotate(t_philo_three *phil);
int					is_alpha(const char *str);
char				*ft_strjoinfreeboth(char *s1, char *s2,
				int lens1, int lens2);
char				*ft_strdup(const char *src);
void				*check_death(t_philo_three *phil);
char				*ft_itoa(int n);
size_t				ft_strlen(const char *s);

#endif
