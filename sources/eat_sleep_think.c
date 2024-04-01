/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:10:55 by egomez-g          #+#    #+#             */
/*   Updated: 2024/02/18 14:57:55 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_one_philo(t_all *all)
{
	int	time;

	all->data->ini_time = get_time_ms();
	time = get_time_ms() - all->data->ini_time;
	printf("%d 1 is thinking\n", time);
	time = get_time_ms() - all->data->ini_time;
	printf("%d 1 has taken a fork\n", time);
	usleep_functional(all->data->die_time);
	time = get_time_ms() - all->data->ini_time;
	printf("%d 1 died\n", time);
}

int	check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->can_start_mutex);
	if (philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->can_start_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->can_start_mutex);
	return (0);
}

static void	aux_eat(t_philo *philo)
{
	action_print(philo, FORK);
	action_print(philo, EAT);
	pthread_mutex_lock(&philo->data->last_eat_time_mutex);
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->data->last_eat_time_mutex);
	pthread_mutex_lock(&philo->times_eat_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eat_mutex);
	usleep_functional(philo->data->eat_time);
	pthread_mutex_lock(&philo->data->last_eat_time_mutex);
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->data->last_eat_time_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	aux_forks_mutex(t_philo *philo)
{
	if (philo->id_philo % 2 == 1)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	if (check_end(philo))
	{
		if (philo->id_philo % 2 == 1)
			pthread_mutex_unlock(philo->left_fork);
		else
			pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	action_print(philo, FORK);
	return (0);
}

void	eat_check(t_philo *philo)
{
	if (aux_forks_mutex(philo))
		return ;
	if (philo->id_philo % 2 == 1)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (check_end(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	aux_eat(philo);
	if (check_end(philo))
		return ;
	action_print(philo, SLEEP);
	usleep_functional(philo->data->sleep_time);
	if (check_end(philo))
		return ;
	action_print(philo, THINK);
}
