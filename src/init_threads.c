#include "../inc/philosophers.h"

void	ft_create_thread(t_table *table)
{
	long i;

	i = 0;
	while (i < table->nr_philo)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &dog_life, table) != 0)
		{
			printf("Error: failed to create thread\n");
			exit(1);
		}
		i++;
	}
}

void	ft_lock_threads(t_table *table)
{
	long i;

	i = 0;
	while (i < table->nr_philo)
	{
		pthread_mutex_lock(&table->forks[i].fork);
		i++;
	}
}

void	ft_unlock_threads(t_table *table)
{
	long i;

	i = 0;
	while (i < table->nr_philo)
	{
		pthread_mutex_unlock(&table->forks[i].fork);
		i++;
	}
}

void	ft_thread_join(t_table *table)
{
	long i;

	i = 0;
	while (i < table->nr_philo)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
		{
			printf("Error: failed to join thread\n");
			exit(1);
		}
		i++;
	}
}
