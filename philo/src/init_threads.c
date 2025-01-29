/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:17:15 by pesilva-          #+#    #+#             */
/*   Updated: 2025/01/26 10:28:20 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_create_thread(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nr_philo)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, \
						&dog_life, &table->philos[i]) != 0)
		{
			printf("Error: failed to create thread\n");
			return ;
		}
		ft_set_bool(&table->philos[i].philo_mute, &table->philos[i].sync_phi, true);
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &monitor_routine, table) != 0)
	{
		printf("Error: failed to create the monitor");
		return ;
	}

}

void	ft_lock_threads(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nr_philo)
	{
		ft_mutex_handler(&table->forks[i].fork, LOCK);
		ft_mutex_handler(&table->philos[i].philo_mute, LOCK);
		i++;
	}
	ft_mutex_handler(&table->print, LOCK);
	ft_mutex_handler(&table->table_mute, LOCK);
}

void	ft_unlock_threads(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nr_philo)
	{
		ft_mutex_handler(&table->forks[i].fork, UNLOCK);
		ft_mutex_handler(&table->philos[i].philo_mute, UNLOCK);
		i++;
	}
	ft_mutex_handler(&table->print, UNLOCK);
	ft_mutex_handler(&table->table_mute, UNLOCK);
}

void	ft_thread_join(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nr_philo && !ft_get_bool(&table->table_mute, \
			&table->stop_simulation))
	{
		if (ft_get_bool(&table->table_mute, &table->stop_simulation))
			break ;
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
		{
			printf("Error: failed to join thread\n");
			return ;
		}
		i++;
	}
	if (pthread_detach(table->monitor) != 0)
	{
		printf("Error: failed to join thread\n");
		return ;
	}
}
