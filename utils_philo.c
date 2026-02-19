/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:44:46 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/18 23:32:36 by rchaumei         ###   ########.fr       */
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

int	ft_usleep(long int start, int sleep)
{
	long int	current_time;

	current_time = get_time();
	while (current_time - start < sleep)
		current_time = get_time();
	return (0);
}
