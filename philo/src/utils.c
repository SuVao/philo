/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:10:32 by pesilva-          #+#    #+#             */
/*   Updated: 2025/01/26 12:10:04 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_timez(long eat, long sleep, long die)
{
	if (eat <= 1)
		return (0);
	if (sleep <= 1)
		return (0);
	if (die <= 1)
		return (0);
	return (1);
}

void	init_table(char **av, t_table **table)
{
	*table = malloc(sizeof(t_table));
	if (!(*table))
	{
		printf("Error: memory allocation failed\n");
		return ;
	}
	(*table)->sync = false;
	ft_mutex_handler(&(*table)->table_mute, INIT);
	ft_mutex_handler(&(*table)->print, INIT);
	(*table)->stop_simulation = false;
	(*table)->nr_philo = ft_atol(av[1]);
	(*table)->time_to_die = ft_atol(av[2]);
	(*table)->time_to_eat = ft_atol(av[3]);
	(*table)->time_to_sleep = ft_atol(av[4]);
	(*table)->philo_seated = 0;
	(*table)->start_time = 0;
	if (!ft_timez(ft_atol(av[2]), ft_atol(av[3]), ft_atol(av[4])))
		return ;
	if (av[5] == NULL)
		(*table)->nb_of_meals = LLONG_MAX;
	else if (ft_atol(av[5]) == 0)
		return ;
	else
		(*table)->nb_of_meals = ft_atol(av[5]);
}

void	ft_dead(t_philo *philo, long time)
{
	printf("%ld philo %d is dead\n", time, \
		ft_get_int(&philo->philo_mute, &philo->philo_id));
}

void	ft_think(t_philo *philo, long time)
{
	printf("%ld %d is thinking\n", time, \
		ft_get_int(&philo->philo_mute, &philo->philo_id));
}

void	printf_mutex(t_printf_mutex status, t_philo *philo)
{
	long	time;

	time = get_current_time(philo->table);
	if (philo->full)
		return ;
	ft_mutex_handler(&philo->table->print, LOCK);
	if ((LEFT_FORK == status || RIGHT_FORK == status) && \
		!ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
		printf("%ld %d take the fork\n", time, \
			ft_get_int(&philo->philo_mute, &philo->philo_id));
	if (EAT == status && \
		!ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
		printf("%ld %d is eating\n", time, \
				ft_get_int(&philo->philo_mute, &philo->philo_id));
	if (SLEEP == status && \
		!ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
		printf("%ld %d is sleeping\n", time, \
			ft_get_int(&philo->philo_mute, &philo->philo_id));
	if (THINKING == status && \
		!ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
		ft_think(philo, time);
	if (DEAD == status)
		ft_dead(philo, time);
	ft_mutex_handler(&philo->table->print, UNLOCK);
}
