
#include "../inc/philosophers.h"
#include <pthread.h>


void	washing_dishes(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nr_philo)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
}

void	kickoff_the_clients(t_table *table)
{
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}
