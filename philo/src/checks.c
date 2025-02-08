/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:06:31 by pesilva-          #+#    #+#             */
/*   Updated: 2025/02/08 01:08:06 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	ft_check_time(t_table *table)
{
	if (table->time_to_die <= 59)
	{
		printf("Error: time to die must be at least 60\n");
		return (false);
	}
	if (table->time_to_eat <= 59)
	{
		printf("Error: time to eat must be at least 60\n");
		return (false);
	}
	if (table->time_to_sleep <= 59)
	{
		printf("Error: time to sleep must be at least 60\n");
		return (false);
	}
	return (true);
}

bool	check_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == 0)
		{
			printf("Void argument\n");
			return (false);
		}
		i++;
	}
	return (true);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i] == NULL)
			return (1);
		while (av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

bool	ft_check_philo_nr(t_table *table)
{
	if (table->nr_philo < 1 || table->nr_philo > 200)
	{
		printf("Invalid nunber of philos\n");
		return (false);
	}
	return (true);
}

void	ft_think(t_philo *philo, long time)
{
	printf("%ld %d is thinking\n", time, \
		ft_get_int(&philo->philo_mute, &philo->philo_id));
}
