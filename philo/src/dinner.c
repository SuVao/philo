/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:07:06 by pesilva-          #+#    #+#             */
/*   Updated: 2025/02/08 16:26:54 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	mutex_threads(t_table *table, t_philo *philo)
{
	(void)philo;
	ft_create_thread(table);
	ft_thread_join(table);
	ft_set_bool(&table->table_mute, &table->stop_simulation, true);
}

void	ft_mutex_handler(pthread_mutex_t *mutex, t_code code)
{
	if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
}

void	ft_sync_threads(t_philo *philos)
{
	while (!ft_get_bool(&philos->table->table_mute, &philos->table->sync))
		;
}

void	ft_one_more_seated(pthread_mutex_t *mutex, int *philo_seated)
{
	ft_mutex_handler(mutex, LOCK);
	(*philo_seated)++;
	ft_mutex_handler(mutex, UNLOCK);
}

void	*dog_life(void *philo1)
{
	t_philo	*philo;

	philo = (t_philo *)philo1;
	ft_sync_threads(philo);
	ft_one_more_seated(&philo->table->table_mute, &philo->table->philo_seated);
	ft_set_long(&philo->philo_mute, &philo->last_meal_time, \
		get_current_time(philo->table));
	while (!ft_get_stop(&philo->table->table_mute, \
						&philo->table->stop_simulation))
	{
		ft_eat_routine(philo);
		if (ft_get_bool(&philo->philo_mute, &philo->full))
			return (NULL);
		printf_mutex(SLEEP, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		ft_philo_thinks(philo);
	}
	return (NULL);
}
