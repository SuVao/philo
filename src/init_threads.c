#include "../inc/philosophers.h"

void	ft_create_thread(void)
{
	long i;

	i = 0;
	while (i < table()->nr_philo)
	{
		pthread_create(&table()->philos[i].thread_id, NULL, &dog_life, &table()->philos[i]);
		i++;
	}
}

void	ft_lock_threads(void)
{
	long i;

	i = 0;
	while (i < table()->nr_philo)
	{
		pthread_mutex_lock(&table()->forks[i].fork);
		i++;
	}
}

void	ft_unlock_threads(void)
{
	long i;

	i = 0;
	while (i < table()->nr_philo)
	{
		pthread_mutex_unlock(&table()->forks[i].fork);
		i++;
	}
}

void	ft_thread_join(void)
{
	long i;

	i = 0;
	while (i < table()->nr_philo)
	{
		pthread_join(table()->philos[i].thread_id, NULL);
		i++;
	}
}
