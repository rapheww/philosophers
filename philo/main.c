/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:17:14 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/22 15:02:22 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_forks(t_p *p, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&p->ph[j].lf);
		j++;
	}
	pthread_mutex_destroy(&p->arg.eating);
	pthread_mutex_destroy(&p->arg.write);
	pthread_mutex_destroy(&p->arg.death);
	pthread_mutex_destroy(&p->arg.beginning);
	return (1);
}

void	finish(t_p *p)
{
	int	i;

	pthread_mutex_destroy(&p->arg.eating);
	pthread_mutex_destroy(&p->arg.write);
	pthread_mutex_destroy(&p->arg.death);
	pthread_mutex_destroy(&p->arg.beginning);
	i = 0;
	while (i < p->arg.n_philo)
	{
		pthread_mutex_destroy(&p->ph[i].lf);
		i++;
	}
	free(p->ph);
}

int	alone(t_philo *p)
{
	pthread_mutex_lock(&p->lf);
	print_philo(p, "has taken a fork");
	pthread_mutex_unlock(&p->lf);
	while (death(p->arg) == 0)
		usleep(100);
	return (1);
}

int	main(int ac, char **av)
{
	t_p	p;
	int	i;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Too few or too many arguments", 2), 1);
	if (check_arg(ac, av, &p))
		return (ft_putstr_fd("An argument is invalid", 2), 1);
	if (ac == 6 && atoi(av[5]) == 0)
		return (0);
	p.ph = malloc(sizeof(t_philo) * p.arg.n_philo);
	if (init(&p) == 1)
		return (free(p.ph), 1);
	i = -1;
	pthread_mutex_lock(&p.arg.beginning);
	while (++i < p.arg.n_philo)
		pthread_create(&p.ph[i].thread_id, NULL, routine, &p.ph[i]);
	pthread_create(&p.arg.thread, NULL, check_end, &p);
	pthread_mutex_unlock(&p.arg.beginning);
	i = -1;
	while (++i < p.arg.n_philo)
		pthread_join(p.ph[i].thread_id, NULL);
	pthread_join(p.arg.thread, NULL);
	return (finish(&p), 0);
}
