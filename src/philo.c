/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:04:50 by pesilva-          #+#    #+#             */
/*   Updated: 2025/01/25 19:17:35 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	init_philo_opc(char **av)
{
	t_table	*table;
	t_philo	*philo;
	t_fork	*forks_table;

	table = NULL;
	philo = NULL;
	forks_table = NULL;
	if (check_args(av) == 1 && !check_av(av))
	{
		printf("Error: wrong arguments\n");
		return ;
	}
	init_table(av, &table);
	if (!ft_check_philo_nr(table) || !ft_check_time(table))
	{
	    free(table);
		return ;
	}
	if (!ft_timez(table->time_to_die, \
		table->time_to_sleep, table->time_to_eat))
	{
		free(table);
		return ;
	}
	table->start_time = get_current_time(table);
	puting_the_forks_on_the_table(table, &forks_table);
	if (forks_table == NULL)
		return ;
	table->philos = philo;
	table->forks = forks_table;
	seating_the_gentlemans(table, &philo);
	mutex_threads(table, philo);
	washing_dishes(table);
}

int	main(int ac, char **av)
{
	if (ft_atol(av[1]) == 1)
	{
		printf("%s the philo is dead!\n", av[2]);
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
