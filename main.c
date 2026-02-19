/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:17:14 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/20 00:37:07 by rchaumei         ###   ########.fr       */
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
		printf("%ldms %i %s\n", (get_time() - ph->arg->start_t), ph->id, s);
	pthread_mutex_unlock(&ph->arg->write);
}

void	*check_death(void *data)
{
	t_p		*p;
	int		i;
	long	current;
	long	eat;

	p = (t_p *)data;
	while (!death(&p->arg))
	{
		i = 0;
		while (i < p->arg.n_philo)
		{
			current = get_time();
			pthread_mutex_lock(&p->arg.eating);
			eat = p->ph[i].eat_time;
			pthread_mutex_unlock(&p->arg.eating);
			if (current - eat >= p->arg.die)
			{
				pthread_mutex_lock(&p->arg.write);
				printf("%ldms %i died\n", (get_time() - p->arg.start_t),
					p->ph[i].id);
				set_death(&p->arg);
				pthread_mutex_unlock(&p->arg.write);
				return (0);
			}
			i++;
		}
		ft_usleep(get_time(), 100);
	}
	return (0);
}

void	*routine(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	if (p->id % 2 == 0)
		ft_usleep(get_time(), 400);
	while (death(p->arg) == 0)
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
		pthread_mutex_lock(&p->arg->eating);
		p->eat_time = get_time();
		p->count_eat++;
		pthread_mutex_unlock(&p->arg->eating);
		print_philo(p, "is eating");
		if (!death(p->arg))
			ft_usleep(get_time(), p->arg->eat);
		pthread_mutex_unlock(&p->lf);
		pthread_mutex_unlock(p->rf);
		print_philo(p, "is sleeping");
		if (!death(p->arg))
			ft_usleep(get_time(), p->arg->sleep);
		print_philo(p, "is thinking");
		if (!death(p->arg))
			ft_usleep(get_time(), 100);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_p	p;
	int	i;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Too few or too many arguments", 2), 1);
	if (check_arg(ac, av, &p))
		return (ft_putstr_fd("An argument is invalid", 2), 1);
	p.ph = malloc(sizeof(t_philo) * p.arg.n_philo);
	init(&p);
	i = 0;
	while (i < p.arg.n_philo)
	{
		pthread_create(&p.ph[i].thread_id, NULL, routine, &p.ph[i]);
		i++;
	}
	pthread_create(&p.arg.thread, NULL, check_death, &p);
	i = 0;
	while (i < p.arg.n_philo)
	{
		pthread_join(p.ph[i].thread_id, NULL);
		i++;
	}
	pthread_join(p.arg.thread, NULL);
	return (0);
}
