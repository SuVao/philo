#include "../inc/philosophers.h"

void	*dog_life(void *table1)
{
	long i;
	t_table    *table;


	table = (t_table *)table1;
	printf("nbr of philos: %ld\n", (long)table->nr_philo);
	i = 0;
	if (table->nr_philo % 2 == 0)
	{
		while (i < table->nr_philo)
		{
			table_for_pair_philos(i, table);
			i++;
		}
	}
	else
	{
		while (i < table->nr_philo)
		{
			table_for_odd_philos(i, table);
			i++;
		}
	}
	return (NULL);
}

void	ft_lock_fork_for_pair(long i, t_table *table)
{
    if (!table || !table->forks)
	{
		printf("Error: table or forks is NULL\n");
		return;
	}
	pthread_mutex_lock(&table->forks[i].fork);
	pthread_mutex_lock(&table->forks[(i + 1) % table->nr_philo].fork);
}

void	ft_unlock_fork_for_pair(long i, t_table *table)
{
    if (!table || !table->forks)
	{
		printf("Error: table or forks is NULL\n");
		return;
	}
	pthread_mutex_unlock(&table->forks[i].fork);
	pthread_mutex_unlock(&table->forks[(i + 1) % table->nr_philo].fork);
}

void	ft_lock_fork_for_odd(long i, t_table *table)
{
    if (!table || !table->forks)
	{
		printf("Error: table or forks is NULL\n");
		return;
	}
	pthread_mutex_lock(&table->forks[(i + 1) % table->nr_philo].fork);
	pthread_mutex_lock(&table->forks[i].fork);
}

void	ft_unlock_fork_for_odd(long i, t_table *table)
{
    if (!table || !table->forks)
	{
		printf("Error: table or forks is NULL\n");
		return;
	}
	pthread_mutex_unlock(&table->forks[(i + 1) % table->nr_philo].fork);
	pthread_mutex_unlock(&table->forks[i].fork);
}
