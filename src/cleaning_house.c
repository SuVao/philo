
#include "../inc/philosophers.h"

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
