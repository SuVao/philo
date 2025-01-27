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
#include <stdbool.h>

void	ft_philo_thinks(t_philo *philo)
{
	printf_mutex(THINKING, philo);
	ft_usleep(50, philo->table);
	if (ft_get_long(&philo->table->table_mute, \
					&philo->table->nr_philo) % 2 == 1)
		ft_usleep(50, philo->table);
}

bool	all_full(t_philo *philo)
{
	long	i;

	i = 0;
	while (i < ft_get_long(&philo->table->table_mute, &philo->table->nr_philo))
	{
		//printf("philo:%ld full: %i\n", i+1, ft_get_bool(&philo->philo_mute, &philo->full));
		if (ft_get_long(&philo[i].philo_mute, &philo[i].nb_philo_meals) == \
			ft_get_long(&philo->table->table_mute, &philo->table->nb_of_meals))
			ft_set_bool(&philo[i].philo_mute, &philo[i].full, true);
		else
			return (false);
		i++;
	}
	return (true);
}

// void	eat_rest(t_philo *philo)
// {
// 	long	i;

// 	i = 0;
// 	while (i < ft_get_long(&philo->table->table_mute, &philo->table->nr_philo) && \
// 			!all_full(philo))
// 	{
// 		if (!ft_get_bool(&philo[i].philo_mute, &philo[i].full))
// 			ft_eat_routine(philo);
// 		else
// 			ft_philo_thinks(philo);
// 		i++;
// 	}
// }
//
// unsigned int	get_time_think(unsigned int nbr_philos,
		unsigned int time_to_sleep, unsigned int time_to_eat)
{
	if (nbr_philos % 2 == 0)
	{
		if (time_to_eat > time_to_sleep)
			return (time_to_eat - time_to_sleep);
		return (0);
	}
	else
	{
		if (time_to_eat * 2 > time_to_sleep)
			return (time_to_eat * 2 - time_to_sleep);
		return (0);
	}
}

/**
 * @brief Introduces an initial delay for philosophers to stagger their actions.

 *
 * @param philo Pointer to the philosopher structure.
 * @return Always returns 1 after applying the delay.
 */
int	initial_usleep(t_philo *philo)
{
	if (philo->table->nbr_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(philo->table->time_to_eat);
	}
	else
	{
		if (philo->id == philo->table->nbr_philos)
			usleep(philo->table->time_to_eat * 2);
		else if (philo->id % 2 == 0)
			usleep(philo->table->time_to_eat);
	}
	return (1);
}


void	ft_eat_routine(t_philo *philo)
{
	long	time;

	ft_mutex_handler(&philo->left_fork->fork, LOCK);
	printf_mutex(LEFT_FORK, philo);
	ft_mutex_handler(&philo->right_fork->fork, LOCK);
	printf_mutex(RIGHT_FORK, philo);
	time = get_current_time(philo->table);
	ft_set_long(&philo->philo_mute, &philo->last_meal_time, time);
	printf_mutex(EAT, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	ft_set_long(&philo->philo_mute, &philo->nb_philo_meals, \
		ft_get_long(&philo->philo_mute, &philo->nb_philo_meals) + 1);
	if (ft_get_long(&philo->table->table_mute, &philo->table->nb_of_meals) > 0 \
		&& all_full(philo))
	{
		ft_set_bool(&philo->table->table_mute, \
					&philo->table->stop_simulation, true);
		return ;
	}
	ft_mutex_handler(&philo->left_fork->fork, UNLOCK);
	ft_mutex_handler(&philo->right_fork->fork, UNLOCK);
}
