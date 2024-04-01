/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:48:47 by egomez-g          #+#    #+#             */
/*   Updated: 2024/02/14 14:44:42 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

enum
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DEAD
};

typedef struct s_data
{
	int				num_philo;
	unsigned int	die_time;
	int				eat_time;
	int				sleep_time;
	int				times_to_eat;
	size_t			ini_time;
	int				can_start;
	pthread_mutex_t	can_start_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	last_eat_time_mutex;
	int				end;
}	t_data;

typedef struct s_philo
{
	int				id_philo;
	size_t			last_eat;
	int				times_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	times_eat_mutex;
	t_data			*data;
}	t_philo;

typedef struct s_all
{
	t_philo			*philos;
	pthread_t		*threads;
	t_data			*data;
	pthread_mutex_t	*forks;
	pthread_t		cont;
}	t_all;

int		atoi_philo(const char *str);
void	action_print(t_philo *philo, int status);
int		parse(char **argv);

//////////////////////////TIMES//////////////////////////
size_t	get_time_ms(void);
size_t	real_time_ms(t_philo *philo);
void	usleep_functional(size_t time);

/////////////////////////THREADS/////////////////////////
void	do_threads(t_all *all);
void	eat_check(t_philo *philo);
int		check_end(t_philo *philo);
int		all_ate(t_all *all);
void	do_one_philo(t_all *all);
void	wait_threads(t_all *all);

#endif