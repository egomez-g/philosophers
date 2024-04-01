/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:50:09 by egomez-g          #+#    #+#             */
/*   Updated: 2024/02/18 14:56:20 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	get_time_ms(void)
{
	size_t			sol;
	struct timeval	time;

	gettimeofday(&time, NULL);
	sol = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (sol);
}

size_t	real_time_ms(t_philo *philo)
{
	size_t	actual_time;

	actual_time = get_time_ms();
	return (actual_time - philo->data->ini_time);
}

void	usleep_functional(size_t time)
{
	size_t	begin;

	begin = get_time_ms();
	while (get_time_ms() - begin < time)
		usleep(250);
}

void	action_print(t_philo *philo, int status)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write_mutex);
	time = real_time_ms(philo);
	if (check_end(philo))
	{
		pthread_mutex_unlock(&philo->data->write_mutex);
		return ;
	}
	if (status == EAT)
		printf("%zu %d is eating\n", time, philo->id_philo);
	else if (status == SLEEP)
		printf("%lu %d is sleeping\n", time, philo->id_philo);
	else if (status == THINK)
		printf("%lu %d is thinking\n", time, philo->id_philo);
	else if (status == FORK)
		printf("%lu %d has taken a fork\n", time, philo->id_philo);
	else
		printf("%lu %d died\n", time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

int	all_ate(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data->num_philo)
	{
		pthread_mutex_lock(&all->philos[i].times_eat_mutex);
		if (all->philos[i].times_eaten < all->data->times_to_eat)
		{
			pthread_mutex_unlock(&all->philos[i].times_eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&all->philos[i].times_eat_mutex);
		i++;
	}
	return (1);
}
