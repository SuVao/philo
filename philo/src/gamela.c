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
		return (true);
	if (ft_get_long(&philo->table->table_mute, &philo->table->time_to_sleep) + \
		ft_get_long(&philo->table->table_mute, &philo->table->time_to_eat) > \
		ft_get_long(&philo->table->table_mute, &philo->table->time_to_die))
		return (true);
	time = get_current_time(philo->table) - \
			(ft_get_long(&philo->philo_mute, &philo->last_meal_time));
	t_die = ft_get_long(&philo->philo_mute, &philo->table->time_to_die);

	if (time < t_die)
		return (false);
	return (true);
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

bool	all_full(t_philo *philo)
{
	long	i;

	i = 0;
	while (i < ft_get_long(&philo->table->table_mute, &philo->table->nr_philo))
	{
		//printf("philo:%ld full: %i\n", i+1, ft_get_bool(&philo->philo_mute, &philo->full));
		if (ft_get_long(&philo[i].philo_mute, &philo[i].nb_philo_meals) != \
			ft_get_long(&philo->table->table_mute, &philo->table->nb_of_meals))
			return (false);
		else
		{
			ft_set_bool(&philo[i].philo_mute, &philo[i].full, true);
			i++;
		}
	}
	return (true);
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
	while (!ft_get_bool(&table->table_mute, &table->stop_simulation))
	{
		while (i < table->nr_philo && !ft_get_stop(&table->table_mute, \
				&table->stop_simulation))
		{
			//if (ft_get_long(&table->philos->philo_mute, &table->philos->nb_philo_meals) == \
			//	ft_get_long(&table->table_mute, &table->nb_of_meals))
			//	ft_set_stop(&table->table_mute, &table->stop_simulation, true);
			//if (all_full(philo->table->philos))
			//	return (NULL);
			//if (all_full(table->philos))
			//	ft_set_stop(&table->table_mute, &table->stop_simulation, true);
			if (found_dead_philo(table->philos + i))
			{
				ft_set_stop(&table->table_mute, &table->stop_simulation, \
							true);
				printf_mutex(DEAD, &table->philos[i]);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
