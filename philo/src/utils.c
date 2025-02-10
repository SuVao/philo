/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:10:32 by pesilva-          #+#    #+#             */
/*   Updated: 2025/02/08 01:07:36 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_timez(long eat, long sleep, long die)
{
	if (eat < 60)
		return (0);
	if (sleep < 60)
		return (0);
	if (die < 60)
		return (0);
	return (1);
}

static void	init_data(t_table *table, char **av)
{
	table->nr_philo = (int)ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->philo_seated = 0;
	table->start_time = 0;
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
	(*table)->sync = false;
	init_data(*table, av);
	if (!ft_timez(ft_atol(av[2]), ft_atol(av[3]), ft_atol(av[4])))
		return ;
	if (av[5] == NULL)
		(*table)->nb_of_meals = INT_MAX;
	else
		(*table)->nb_of_meals = ft_atol(av[5]);
}

void	printf_mutex(t_printf_mutex status, t_philo *philo)
{
	long	time;

	time = get_current_time(philo->table);
	ft_mutex_handler(&philo->table->print, LOCK);
	if ((LEFT_FORK == status || RIGHT_FORK == status) && \
		!ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
		printf("%ld %d has taken a fork\n", time, philo->philo_id);
	if (EAT == status && \
		!ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
		printf("%ld %d is eating\n", time, philo->philo_id);
	if (SLEEP == status && \
		!ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
		printf("%ld %d is sleeping\n", time, philo->philo_id);
	if (THINKING == status && \
		!ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
		ft_think(philo, time);
	if (DEAD == status)
		printf("%ld %d died\n", time, philo->philo_id);
	ft_mutex_handler(&philo->table->print, UNLOCK);
}

int	ft_get_int(pthread_mutex_t *mutex, int *val)
{
	int	val_ret;

	ft_mutex_handler(mutex, LOCK);
	val_ret = *val;
	ft_mutex_handler(mutex, UNLOCK);
	return (val_ret);
}
