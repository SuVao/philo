/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamela.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:07:54 by pesilva-          #+#    #+#             */
/*   Updated: 2025/01/26 10:18:53 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	found_dead_philo(t_philo *philo)
{
	long	t_die;
	long	time;

	if (all_full(philo))
		return (false);
	time = get_current_time(philo->table) - \
			ft_get_long(&philo->philo_mute, &philo->last_meal_time);
	t_die = ft_get_long(&philo->philo_mute, &philo->table->time_to_die);
	if (time < t_die)
		return (true);
	return (false);
}

bool	all_philo_seats(pthread_mutex_t *mutex, long *philos, long philo_nr)
{
	bool	ola;

	ola = false;
	ft_mutex_handler(mutex, LOCK);
	if (*philos == philo_nr)
		ola = true;
	ft_mutex_handler(mutex, UNLOCK);
	return (ola);
}

bool	ft_get_stop(pthread_mutex_t *mutex, bool *stop)
{
	bool	val;

	ft_mutex_handler(mutex, LOCK);
	val = *stop;
	ft_mutex_handler(mutex, UNLOCK);
	return (val);
}

void	ft_set_stop(pthread_mutex_t *mutex, bool *stop, bool val)
{
	ft_mutex_handler(mutex, LOCK);
	*stop = val;
	ft_mutex_handler(mutex, UNLOCK);
}

void	*monitor_routine(void *table1)
{
	t_table	*table;
	int		i;

	table = (t_table *)table1;
	while (!all_philo_seats(&table->table_mute, \
			&table->philo_seated, table->nr_philo))
		;
	i = 0;
	while (!ft_get_stop(&table->table_mute, &table->stop_simulation))
	{
		while (i < table->nr_philo && !ft_get_stop(&table->table_mute, \
				&table->stop_simulation))
		{
			if (!found_dead_philo(table->philos + i))
			{
				ft_set_stop(&table->table_mute, &table->stop_simulation, \
							true);
				printf_mutex(DEAD, &table->philos[i]);
			}
			i++;
		}
	}
	return (NULL);
}
