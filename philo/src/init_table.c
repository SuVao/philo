/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:19:37 by pesilva-          #+#    #+#             */
/*   Updated: 2025/01/26 10:20:05 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

t_philo	create_philo(t_philo *philos, long i, t_table *table)
{
	philos[i].philo_id = i + 1;
	philos[i].full = false;
	philos[i].thread_id = i;
	philos[i].sync_phi = false;
	philos[i].table = table;
	philos[i].dead = false;
	philos[i].nb_philo_meals = 0;
	philos[i].left_fork = &table->forks[(i + 1) % table->nr_philo];
	philos[i].right_fork = &table->forks[i];
	if (philos[i].philo_id % 2 == 0)
	{
		philos[i].left_fork = &table->forks[i];
		philos[i].right_fork = &table->forks[(i + 1) % table->nr_philo];
	}
	ft_mutex_handler(&philos[i].philo_mute, INIT);
	return (philos[i]);
}

t_fork	create_forks(t_fork *forks_table, long i, t_table *table)
{
	(void)table;
	forks_table[i].fork_id = i;
	ft_mutex_handler(&forks_table[i].fork, INIT);
	return (forks_table[i]);
}

void	puting_the_forks_on_the_table(t_table *table, t_fork **forks_table)
{
	long	i;

	*forks_table = malloc(sizeof(t_fork) * table->nr_philo);
	if (!(*forks_table))
	{
		printf("Error: failed to allocate memory for forks_table\n");
		return ;
	}
	i = 0;
	while (i < table->nr_philo)
	{
		(*forks_table)[i] = create_forks(*forks_table, i, table);
		i++;
	}
	table->forks = *forks_table;
}

void	seating_the_gentlemans(t_table *table, t_philo **philos)
{
	long	i;

	*philos = malloc(sizeof(t_philo) * table->nr_philo);
	if (!(*philos))
	{
		printf("Error: failed to allocate memory for philos\n");
		washing_dishes(table);
		return ;
	}
	table->philos = *philos;
	i = 0;
	while (i < table->nr_philo)
	{
		(*philos)[i] = create_philo(*philos, i, table);
		i++;
	}
}
