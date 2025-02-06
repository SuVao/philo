/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:04:50 by pesilva-          #+#    #+#             */
/*   Updated: 2025/01/26 16:15:14 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static bool	checks_table(t_table *table, char **av)
{
	if (!ft_check_philo_nr(table) || !ft_check_time(table) || \
		ft_atol(av[1]) == 1 || !ft_timez(table->time_to_die, \
		table->time_to_sleep, table->time_to_eat))
	{
		free(table);
		return (false);
	}
	return (true);
}

static void	assigning(t_table **table, t_philo **philo, t_fork **forks)
{
	(*table)->philos = *philo;
	(*table)->forks = *forks;
}

void	init_philo_opc(char **av)
{
	t_table	*table;
	t_philo	*philo;
	t_fork	*forks_table;

	table = NULL;
	philo = NULL;
	forks_table = NULL;
	if (check_args(av) == 1 || !check_av(av))
	{
		printf("Error: wrong arguments\n");
		return ;
	}
	init_table(av, &table);
	if (!checks_table(table, av))
		return ;
	puting_the_forks_on_the_table(table, &forks_table);
	assigning(&table, &philo, &forks_table);
	seating_the_gentlemans(table, &philo);
	table->start_time = get_current_time(table);
	mutex_threads(table, philo);
	washing_dishes(table);
}

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	if (ac == 6 || ac == 5)
		init_philo_opc(av);
	else
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	return (0);
}
