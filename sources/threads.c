/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:39:20 by egomez-g          #+#    #+#             */
/*   Updated: 2024/02/15 13:06:39 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	end_check(t_all *all)
{
	int		i;

	i = 0;
	while (i < all->data->num_philo)
	{
		pthread_mutex_lock(&all->data->last_eat_time_mutex);
		if (get_time_ms() - all->philos[i].last_eat >= all->data->die_time)
		{
			action_print(&all->philos[i], DEAD);
			pthread_mutex_unlock(&all->data->last_eat_time_mutex);
			return (1);
		}
		pthread_mutex_unlock(&all->data->last_eat_time_mutex);
		if (all->data->times_to_eat != -1 && all_ate(all))
			return (1);
		i++;
	}
	return (0);
}

void	*controller(void *arg)
{
	t_all	*all;
	int		start;

	all = (t_all *)arg;
	while (1)
	{
		pthread_mutex_lock(&all->data->can_start_mutex);
		start = all->data->can_start;
		pthread_mutex_unlock(&all->data->can_start_mutex);
		if (start)
			break ;
	}
	while (1)
	{
		if (end_check(all))
		{
			pthread_mutex_lock(&all->data->can_start_mutex);
			all->data->end = 1;
			pthread_mutex_unlock(&all->data->can_start_mutex);
			break ;
		}
	}
	return (NULL);
}

static void	wait_to_start(t_philo *philo)
{
	int		start;

	start = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->can_start_mutex);
		start = philo->data->can_start;
		pthread_mutex_unlock(&philo->data->can_start_mutex);
		if (start)
			break ;
	}
}

void	*do_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_to_start(philo);
	usleep_functional(philo->id_philo - 1);
	action_print(philo, THINK);
	while (1)
	{
		if (check_end(philo))
			break ;
		eat_check(philo);
	}
	return (NULL);
}

void	do_threads(t_all *all)
{
	int	i;

	i = 0;
	all->data->can_start = 0;
	if (all->data->num_philo == 1)
	{
		do_one_philo(all);
		return ;
	}
	while (i < all->data->num_philo)
	{
		all->philos[i].last_eat = get_time_ms();
		all->philos[i].times_eaten = 0;
		pthread_create(&(all->threads[i]), NULL, do_philo, \
		(void *)&all->philos[i]);
		i++;
	}
	pthread_create(&all->cont, NULL, controller, (void *)all);
	all->data->ini_time = get_time_ms();
	pthread_mutex_lock(&all->data->can_start_mutex);
	all->data->can_start = 1;
	pthread_mutex_unlock(&all->data->can_start_mutex);
	wait_threads(all);
}
