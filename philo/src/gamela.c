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

bool	all_full(t_philo *philo)
{
	long	i;

	i = 0;
	while (i < ft_get_long(&philo->table->table_mute, &philo->table->nr_philo))
	{
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

void	waiting_for_philos(t_table *table)
{
	while (!all_philo_seats(&table->table_mute, \
			ft_get_long(&table->table_mute, &table->philo_seated), \
			ft_get_long(&table->table_mute, &table->nr_philo)))
		;
}

bool	check_gamela(t_table *table, int i)
{
	if (found_dead_philo(table->philos + i))
	{
		ft_set_stop(&table->table_mute, &table->stop_simulation, \
					true);
		printf_mutex(DEAD, &table->philos[i]);
		return (false);
	}
	if (all_full(table->philos))
	{
		ft_set_stop(&table->table_mute, &table->stop_simulation, \
					true);
		return (false);
	}
	return (true);
}

void	*monitor_routine(void *table1)
{
	t_table	*table;
	int		i;

	table = (t_table *)table1;
	waiting_for_philos(table);
	i = 0;
	while (!ft_get_bool(&table->table_mute, &table->stop_simulation))
	{
		while (i < table->nr_philo && !ft_get_stop(&table->table_mute, \
				&table->stop_simulation))
		{
			if (!check_gamela(table, i))
				break ;
			i++;
		}
	}
	return (NULL);
}
