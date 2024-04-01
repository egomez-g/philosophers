/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:34:13 by egomez-g          #+#    #+#             */
/*   Updated: 2024/02/14 16:52:25 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_threads(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data->num_philo)
	{
		pthread_join(all->threads[i], NULL);
		i++;
	}
	pthread_join(all->cont, NULL);
}

static int	paco_sans(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	if (atoi_philo(str) == 0)
		return (1);
	return (0);
}

int	parse(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (paco_sans(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
