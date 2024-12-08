
#include "../inc/philosophers.h"
#include <pthread.h>

t_philo	*philo(void)
{
	static t_philo philo;
	return (&philo);
}

t_table	*table(void)
{
	static t_table	table;
	return (&table);
}

void	washing_dishes()
{
	int i;

	i = 0;
	while (i < table()->nr_philo)
	{
		pthread_mutex_destroy(&table()->forks[i].fork);
		i++;
	}
	if (table()->forks)
	{
		free(table()->forks);
		table()->forks = NULL;
	}
}

void	kickoff_the_clients(void)
{
	if (table()->philos)
	{
		free(table()->philos);
		table()->philos = NULL;
	}
}
