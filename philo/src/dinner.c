/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:07:06 by pesilva-          #+#    #+#             */
/*   Updated: 2025/01/26 10:25:55 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	mutex_threads(t_table *table, t_philo *philo)
{
	(void)philo;
	table->shared_fork = 0;
	//ft_lock_threads(table);
	table->shared_fork++;
	//ft_unlock_threads(table);
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
	while (!ft_get_bool(&philos->philo_mute, &philos->sync_phi))
		;
}

void	ft_one_more_seated(pthread_mutex_t *mutex, long *philo_seated)
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
	//printf("sync philos: %i\n", ft_get_bool(&philo->philo_mute, &philo->sync_phi));
	ft_one_more_seated(&philo->table->table_mute, &philo->table->philo_seated);
	ft_set_long(&philo->philo_mute, &philo->last_meal_time, \
				get_current_time(philo->table));
	while (!ft_get_bool(&philo->table->table_mute, \
						&philo->table->stop_simulation))
	{
		if (ft_get_bool(&philo->philo_mute, &philo->full))
			return (NULL);

		ft_eat_routine(philo);
		//printf("philo meal: %ld table meals: %ld\n", ft_get_long(&philo->philo_mute, &philo->nb_philo_meals), \
		//	ft_get_long(&philo->table->table_mute, &philo->table->nb_of_meals));

		//if (ft_get_bool(&philo->philo_mute, &philo->dead))
		//	break ;
		printf_mutex(SLEEP, philo);
		ft_usleep(ft_get_long(&philo->table->table_mute, \
					&philo->table->time_to_sleep), philo->table);
		ft_philo_thinks(philo);
	}
	return (NULL);
}
