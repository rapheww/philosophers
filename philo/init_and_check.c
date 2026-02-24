/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:20:53 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/22 14:44:17 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_p *p)
{
	if (pthread_mutex_init(&p->arg.eating, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&p->arg.write, NULL) != 0)
	{
		pthread_mutex_destroy(&p->arg.eating);
		return (1);
	}
	if (pthread_mutex_init(&p->arg.beginning, NULL) != 0)
	{
		pthread_mutex_destroy(&p->arg.eating);
		pthread_mutex_destroy(&p->arg.write);
		return (1);
	}
	if (pthread_mutex_init(&p->arg.death, NULL) != 0)
	{
		pthread_mutex_destroy(&p->arg.eating);
		pthread_mutex_destroy(&p->arg.write);
		pthread_mutex_destroy(&p->arg.beginning);
		return (1);
	}
	return (0);
}

int	init(t_p *p)
{
	int	i;

	i = 0;
	p->arg.n_finish = 0;
	p->arg.start_t = get_time();
	if (init_mutex(p) == 1)
		return (1);
	while (i < p->arg.n_philo)
	{
		p->ph[i].arg = &p->arg;
		p->ph[i].count_eat = 0;
		p->ph[i].eat_time = p->arg.start_t;
		p->ph[i].id = i + 1;
		p->ph[i].rf = NULL;
		if (pthread_mutex_init(&p->ph[i].lf, NULL) != 0)
			return (destroy_forks(p, i));
		if (p->arg.n_philo == 1)
			return (0);
		if (i == p->arg.n_philo - 1)
			p->ph[i].rf = &p->ph[0].lf;
		else
			p->ph[i].rf = &p->ph[i + 1].lf;
		i++;
	}
	return (0);
}

int	len_arg(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		if (ft_strlen(av[i]) > 11)
			return (1);
	return (0);
}

int	fill_arg(int ac, char **av, t_p *p)
{
	p->arg.n_philo = ft_atoi(av[1]);
	p->arg.die = ft_atoi(av[2]);
	p->arg.eat = ft_atoi(av[3]);
	p->arg.sleep = ft_atoi(av[4]);
	p->arg.ac = ac;
	p->arg.dead = 0;
	if (ac == 6)
	{
		p->arg.n_eat = ft_atoi(av[5]);
		if (p->arg.n_eat < 0)
			return (1);
	}
	if (p->arg.n_philo <= 0 || p->arg.die <= 0 || p->arg.eat <= 0
		|| p->arg.sleep <= 0)
		return (1);
	return (0);
}

int	check_arg(int ac, char **av, t_p *p)
{
	int	i;
	int	j;

	i = 1;
	if (checks_lim(ac, av) || len_arg(av))
		return (1);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_digit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (fill_arg(ac, av, p));
}
