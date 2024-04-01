/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:47:29 by egomez-g          #+#    #+#             */
/*   Updated: 2024/02/14 15:30:20 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_all(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data->num_philo)
	{
		pthread_mutex_destroy(&(all->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(all->data->write_mutex));
	free(all->threads);
	free(all->forks);
	free(all->data);
}

static t_data	*init_data(char **argv, int argc)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	data->num_philo = atoi_philo(argv[1]);
	data->die_time = atoi_philo(argv[2]);
	data->eat_time = atoi_philo(argv[3]);
	data->sleep_time = atoi_philo(argv[4]);
	if (argc == 6)
		data->times_to_eat = atoi_philo(argv[5]);
	else
		data->times_to_eat = -1;
	pthread_mutex_init((pthread_mutex_t *)(&data->write_mutex), NULL);
	pthread_mutex_init((pthread_mutex_t *)(&data->last_eat_time_mutex), NULL);
	data->end = 0;
	return (data);
}

static void	init_philos(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data->num_philo)
	{
		all->philos[i].data = all->data;
		all->philos[i].id_philo = i + 1;
		all->philos[i].left_fork = &all->forks[i];
		if (i == all->data->num_philo - 1)
			all->philos[i].right_fork = &(all->forks[0]);
		else
			all->philos[i].right_fork = &(all->forks[i + 1]);
		pthread_mutex_init((pthread_mutex_t *) \
		(&all->philos[i].times_eat_mutex), NULL);
		i++;
	}
}

static void	init_struct(t_all *all, char **argv, int argc)
{
	int	i;

	all->data = init_data(argv, argc);
	all->threads = malloc (sizeof(pthread_t) * (all->data->num_philo + 1));
	if (!all->threads)
		return ;
	all->threads[all->data->num_philo] = NULL;
	all->forks = malloc (sizeof(pthread_mutex_t) * (all->data->num_philo));
	if (!all->forks)
		return ;
	all->philos = malloc (sizeof(t_philo) * (all->data->num_philo));
	if (!all->forks)
		return ;
	i = 0;
	while (i < all->data->num_philo)
	{
		pthread_mutex_init(&(all->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init((pthread_mutex_t *)(&all->data->can_start_mutex), NULL);
	init_philos(all);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 5 && argc != 6)
	{
		printf("Error: invalid arguments\n");
		return (0);
	}
	if (parse(argv))
	{
		printf("Error: bad input\n");
		return (0);
	}
	init_struct(&all, argv, argc);
	do_threads(&all);
	free_all(&all);
	return (0);
}
