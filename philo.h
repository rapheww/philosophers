/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:36:49 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/19 23:20:39 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// STRUCTURE

typedef struct s_arg
{
	int ac;
	pthread_mutex_t	 beginning;
	int				n_philo;
	long			start_t;
	int				die;
	int				dead;
	int				eat;
	int				sleep;
	int				n_eat;
	int				n_finish;
	pthread_t		thread;
	pthread_mutex_t	write;
	pthread_mutex_t	eating;
	pthread_mutex_t	death;
}					t_arg;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				count_eat;
	long int		eat_time;
	t_arg			*arg;
	pthread_mutex_t	*rf;
	pthread_mutex_t	lf;
}					t_philo;

typedef struct s_p
{
	t_philo			*ph;
	t_arg			arg;
}					t_p;

// INIT

int					init(t_p *p);
int					fill_arg(int ac, char **av, t_p *p);
int					check_arg(int ac, char **av, t_p *p);
int					len_arg(char **av);

// CHECK LIMITS

int					checks_lim(int ac, char **av);

// UTILS

int					ft_digit(char c);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
int					ft_atoi(const char *str);
int					ft_strlen(char *s);
long				get_time(void);
int					ft_usleep(long int start, int sleep);

#endif