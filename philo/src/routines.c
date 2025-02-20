/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:06:23 by pesilva-          #+#    #+#             */
/*   Updated: 2025/02/08 01:05:42 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	ft_get_stop(pthread_mutex_t *mutex, bool *stop)
{
	bool	val;

	ft_mutex_handler(mutex, LOCK);
	val = *stop;
	ft_mutex_handler(mutex, UNLOCK);
	return (val);
}

void	set_eat_data(t_philo *philo, long time)
{
	ft_set_long(&philo->philo_mute, &philo->last_meal_time, time);
	ft_set_int(&philo->philo_mute, &philo->nb_philo_meals, \
		ft_get_int(&philo->philo_mute, &philo->nb_philo_meals) + 1);
}

void	ft_eat_routine(t_philo *philo)
{
	long	time;

	ft_mutex_handler(&philo->left_fork->fork, LOCK);
	printf_mutex(LEFT_FORK, philo);
	if (philo->table->nr_philo == 1)
	{
	    ft_mutex_handler(&philo->left_fork->fork, UNLOCK);
		return ;
	}
	ft_mutex_handler(&philo->right_fork->fork, LOCK);
	printf_mutex(RIGHT_FORK, philo);
	ft_set_bool(&philo->philo_mute, &philo->is_eat, true);
	printf_mutex(EAT, philo);
	time = get_current_time(philo->table);
	set_eat_data(philo, time);
	ft_usleep(philo->table->time_to_eat, philo->table);
	ft_mutex_handler(&philo->left_fork->fork, UNLOCK);
	ft_mutex_handler(&philo->right_fork->fork, UNLOCK);
	ft_set_bool(&philo->philo_mute, &philo->is_eat, false);
	if (philo->table->nb_of_meals > 0 && ft_get_int(&philo->philo_mute, \
		&philo->nb_philo_meals) == philo->table->nb_of_meals)
	{
		ft_philo_thinks(philo);
		ft_set_bool(&philo->philo_mute, &philo->full, true);
	}
}

void	print_one_dead(char **av)
{
	if (ft_atol(av[4]) > 0)
	{
		printf("0 1 has taken a fork\n");
		while (usleep(ft_atol(av[2]) * 1000))
			;
	}
	printf("%s 1 died\n", av[2]);
}
