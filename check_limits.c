/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_limits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:21:25 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/18 23:33:15 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_temp(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

long	ft_atol(const char *str)
{
	int		i;
	int		signe;
	long	result;

	i = 0;
	signe = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		signe = -signe;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * signe);
}

long	*ft_conv_long(int ac, char **av, int *size, int i)
{
	char	**temp;
	long	*result;
	int		count;

	(count = 0);
	temp = av + 1;
	while (temp[count])
		count++;
	result = malloc(sizeof(long) * count);
	if (!result)
		return (free_temp(temp), NULL);
	while (temp[++i])
		result[i] = ft_atol(temp[i]);
	*size = count;
	if (ac == 2)
		free_temp(temp);
	return (result);
}

int	ft_check_limits(long *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i] < -2147483648 || tab[i] > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

int	checks_lim(int ac, char **av)
{
	long	*tab;
	int		i;
	int		size;

	i = -1;
	tab = ft_conv_long(ac, av, &size, i);
	if (!tab)
		return (0);
	if (ft_check_limits(tab, size))
		return (free(tab), 1);
	free(tab);
	return (0);
}
