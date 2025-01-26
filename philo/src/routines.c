/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:06:23 by pesilva-          #+#    #+#             */
/*   Updated: 2025/01/26 16:08:16 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_philo_thinks(t_philo *philo)
{
	printf_mutex(THINKING, philo);
	if (ft_get_long(&philo->table->table_mute, \
					&philo->table->nr_philo) % 2 == 1)
		ft_usleep(50, philo->table);
}

void	ft_eat_routine(t_philo *philo)
{
	long	time;

	time = get_current_time(philo->table);
	ft_mutex_handler(&philo->left_fork->fork, LOCK);
	printf_mutex(LEFT_FORK, philo);
	ft_mutex_handler(&philo->right_fork->fork, LOCK);
	printf_mutex(RIGHT_FORK, philo);
	ft_set_long(&philo->philo_mute, &philo->last_meal_time, time);
	ft_set_long(&philo->philo_mute, &philo->nb_philo_meals, \
		ft_get_long(&philo->philo_mute, &philo->nb_philo_meals) + 1);
	printf_mutex(EAT, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	//printf("table meal: %ld\n", philo->table->nb_of_meals);
	//printf("philo meal: %ld\n", philo->nb_philo_meals);
	if (ft_get_long(&philo->table->table_mute, &philo->table->nb_of_meals) > 0 \
		&& philo->nb_philo_meals == philo->table->nb_of_meals)
	{
		printf_mutex(DEAD, philo);
		ft_set_bool(&philo->table->table_mute, \
					&philo->table->stop_simulation, true);
		return ;
	}
	ft_mutex_handler(&philo->left_fork->fork, UNLOCK);
	ft_mutex_handler(&philo->right_fork->fork, UNLOCK);
}
