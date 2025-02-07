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
	int    i;

	i = 0;
	while (i < table->nr_philo)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, \
						&dog_life, &table->philos[i]) != 0)
		{
			printf("Error: failed to create thread\n");
			return ;
		}
		i++;
	}
	table->start_time = get_current_time(table);
	ft_set_bool(&table->table_mute, &table->sync, true);
	if (pthread_create(&table->monitor, NULL, &monitor_routine, table) != 0)
	{
		printf("Error: failed to create the monitor");
		return ;
	}
}

bool	all_philo_seats(pthread_mutex_t *mutex, int philos, int philo_nr)
{
	bool	ola;

	ola = false;
	ft_mutex_handler(mutex, LOCK);
	if (philos == philo_nr)
		ola = true;
	ft_mutex_handler(mutex, UNLOCK);
	return (ola);
}

void	ft_set_stop(pthread_mutex_t *mutex, bool *stop, bool val)
{
	ft_mutex_handler(mutex, LOCK);
	*stop = val;
	ft_mutex_handler(mutex, UNLOCK);
}

void	ft_thread_join(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nr_philo)
	{
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
