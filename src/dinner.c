#include "../inc/philosophers.h"

void	*dog_life()
{
	long i;

	i = 0;
	if (table()->nr_philo % 2 == 0)
	{
		while (i < table()->nr_philo)
		{
			table_for_pair_philos(i);
			i++;
		}
	}
	else
	{
		while (i < table()->nr_philo)
		{
			table_for_odd_philos(i);
			i++;
		}
	}
	return (NULL);
}

void	ft_lock_fork_for_pair(long i)
{
	pthread_mutex_lock(&table()->forks[i].fork);
	pthread_mutex_lock(&table()->forks[(i + 1) % table()->nr_philo].fork);
}

void	ft_unlock_fork_for_pair(long i)
{
	pthread_mutex_unlock(&table()->forks[i].fork);
	pthread_mutex_unlock(&table()->forks[(i + 1) % table()->nr_philo].fork);
}

void	ft_lock_fork_for_odd(long i)
{
	pthread_mutex_lock(&table()->forks[(i + 1) % table()->nr_philo].fork);
	pthread_mutex_lock(&table()->forks[i].fork);
}

void	ft_unlock_fork_for_odd(long i)
{
	pthread_mutex_unlock(&table()->forks[(i + 1) % table()->nr_philo].fork);
	pthread_mutex_unlock(&table()->forks[i].fork);
}
