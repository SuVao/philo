/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_house.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:06:38 by pesilva-          #+#    #+#             */
/*   Updated: 2025/02/08 16:27:29 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	washing_dishes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nr_philo)
	{
		ft_mutex_handler(&table->forks[i].fork, DESTROY);
		i++;
	}
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	kickoff_the_clients(table);
}

void	kickoff_the_clients(t_table *table)
{
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}

void	ft_philo_thinks(t_philo *philo)
{
	printf_mutex(THINKING, philo);
	if(philo->table->nr_philo % 2 == 0)
	{
	    if (philo->table->time_to_eat > philo->table->time_to_sleep)
	       usleep((philo->table->time_to_eat - philo->table->time_to_sleep) *1000);
	}
	else
    {
        if (philo->table->time_to_eat * 2 > philo->table->time_to_sleep)
           usleep((philo->table->time_to_eat * 2 - philo->table->time_to_sleep) *1000);
    }
}
