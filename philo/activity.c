/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:51:20 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/22 15:01:25 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	long			time;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (time);
}

int	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (time - (get_time() - start) > 1)
			usleep(500);
		else
			usleep(50);
	}
	return (0);
}

void	lock_fork(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&p->lf);
		print_philo(p, "has taken a fork");
		pthread_mutex_lock(p->rf);
		print_philo(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->rf);
		print_philo(p, "has taken a fork");
		pthread_mutex_lock(&p->lf);
		print_philo(p, "has taken a fork");
	}
}

void	activity(t_philo *p)
{
	pthread_mutex_lock(&p->arg->eating);
	p->eat_time = get_time();
	pthread_mutex_unlock(&p->arg->eating);
	print_philo(p, "is eating");
	if (!death(p->arg))
		ft_usleep(p->arg->eat);
	pthread_mutex_unlock(&p->lf);
	pthread_mutex_unlock(p->rf);
	pthread_mutex_lock(&p->arg->eating);
	p->count_eat++;
	pthread_mutex_unlock(&p->arg->eating);
	print_philo(p, "is sleeping");
	if (!death(p->arg))
		ft_usleep(p->arg->sleep);
	print_philo(p, "is thinking");
	if (!death(p->arg))
		ft_usleep((p->arg->die - (p->arg->eat + p->arg->sleep)) / 2);
}

void	*routine(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	pthread_mutex_lock(&p->arg->beginning);
	pthread_mutex_unlock(&p->arg->beginning);
	if (p->id % 2 == 0)
		ft_usleep((p->arg->die - (p->arg->eat + p->arg->sleep)) / 4);
	if (p->arg->n_philo == 1)
		if (alone(p))
			return (0);
	while (death(p->arg) == 0)
	{
		lock_fork(p);
		activity(p);
	}
	return (0);
}
