/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:55:08 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/22 15:07:49 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death(t_arg *arg)
{
	int	dead_infos;

	pthread_mutex_lock(&arg->death);
	dead_infos = arg->dead;
	pthread_mutex_unlock(&arg->death);
	return (dead_infos);
}

void	set_death(t_arg *arg)
{
	pthread_mutex_lock(&arg->death);
	arg->dead = 1;
	pthread_mutex_unlock(&arg->death);
}

void	print_philo(t_philo *ph, char *s)
{
	pthread_mutex_lock(&ph->arg->write);
	if (!death(ph->arg))
		printf("%ld %i %s\n", (get_time() - ph->arg->start_t), ph->id, s);
	pthread_mutex_unlock(&ph->arg->write);
}

int	checking(t_p *p, int i, int *n_finish)
{
	long	eat;

	pthread_mutex_lock(&p->arg.eating);
	eat = p->ph[i].eat_time;
	if (p->arg.ac == 6)
	{
		if (p->ph[i].count_eat >= p->arg.n_eat)
			(*n_finish)++;
	}
	pthread_mutex_unlock(&p->arg.eating);
	if (get_time() - eat >= p->arg.die)
	{
		pthread_mutex_lock(&p->arg.write);
		printf("%ldms %i died\n", (get_time() - p->arg.start_t), p->ph[i].id);
		set_death(&p->arg);
		pthread_mutex_unlock(&p->arg.write);
		return (1);
	}
	if (*n_finish == p->arg.n_philo)
	{
		set_death(&p->arg);
		return (1);
	}
	return (0);
}

void	*check_end(void *data)
{
	t_p		*p;
	int		i;
	int		n_finish;

	p = (t_p *)data;
	while (!death(&p->arg))
	{
		i = 0;
		n_finish = 0;
		while (i < p->arg.n_philo)
		{
			if (checking(p, i, &n_finish) == 1)
				return (0);
			i++;
		}
		ft_usleep(10);
	}
	return (0);
}
