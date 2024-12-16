#include "../inc/philosophers.h"

t_philo	create_philo(t_philo *philos, long i, t_table *table)
{
	philos[i].philo_id = i;
	philos[i].left_fork = &table->forks[i];
	philos[i].right_fork = &table->forks[(i + 1) % table->nr_philo];
	philos[i].thread_id = i;
	return (philos[i]);
}

t_fork	create_forks(t_fork *forks_table, long i, t_table *table)
{
    (void)table;
	forks_table[i].fork_id = i;
	pthread_mutex_init(&forks_table[i].fork, NULL);
	printf("fork is in use: %ld\n", i);
	return (forks_table[i]);
}

void	puting_the_forks_on_the_table(t_table *table, t_fork **forks_table)
{
	long i;

	*forks_table = malloc(sizeof(t_fork) * table->nr_philo);
	if (!(*forks_table))
	{
		printf("Error: failed to allocate memory for forks_table\n");
		exit(1);
	}

	i = 0;
	while (i < table->nr_philo)
	{
		printf("nr_philo: %ld\n", table->nr_philo);
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
		exit(1);
	}

	table->philos = *philos;

	i = 0;
	while (i < table->nr_philo)
	{
		(*philos)[i] = create_philo(*philos, i, table);
		i++;
	}
}
