
#include "../inc/philosophers.h"

void	washing_dishes(t_table *table)
{
	int i;

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
}

void	kickoff_the_clients(t_table *table)
{
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}
