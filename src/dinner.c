#include "../inc/philosophers.h"

void	mutex_threads(t_table *table)
{
	table->shared_fork = 0;
	ft_lock_threads(table);
	table->shared_fork++;
	ft_unlock_threads(table);
	ft_create_thread(table);
//	table->start_time = get_current_time();
	ft_thread_join(table);
}

void	ft_sync_threads(t_table *table)
{
	long i;

	i = 0;
	while (i < table->nr_philo)
	{
		if (table->philos[i].philo_id % 2 == 1)
		{
			printf("waiting for threads to sync\n");
			ft_usleep(50);
		}
	}
}

void	*dog_life(void *table1)
{
	t_table    *table;
	long i;

	i = 0;
	table = (t_table *)table1;
	//ft_usleep(table->time_to_die);
	//sycnronize the threads
//	ft_sync_threads(table);
	while (!table->dead)
	{
		if (table->nr_philo % 2 == 0)
		{
			ft_lock_fork(i, table);
			printf("%ld %d is eating\n", get_current_time(),table->philos[i].philo_id);
			ft_usleep(table->time_to_eat);
			ft_unlock_fork(i, table);
			printf("Philo %d is sleeping\n", table->philos[i].philo_id);
			//ft_usleep(table->time_to_sleep);
		//	i = (i + 1) % table->nr_philo;
		}
		else
		{
			ft_lock_fork(i, table);
			printf("%ld %d is eating\n", get_current_time(), table->philos[i].philo_id);
			ft_usleep(table->time_to_eat);
			ft_unlock_fork(i, table);
			printf("Philo %d is sleeping\n", table->philos[i].philo_id);

		}
		i = (i + 1) % table->nr_philo;
	}
	return (NULL);
}

void	ft_lock_fork(long i, t_table *table)
{
	long	time;

	time = get_current_time();
    if (!table || !table->forks)
	{
		printf("Error: table or forks is NULL\n");
		return;
	}
	printf("ola\n");
	printf("time: %ld Philo %ld has taken the fork: %d\n", time, i, table->philos[i].philo_id);
	pthread_mutex_lock(&table->forks[i].fork);
	pthread_mutex_lock(&table->forks[(i + 1) % table->nr_philo].fork);
	printf("Philo %d has taken the fork: %ld\n", \
			table->philos[i].philo_id, (i + 1) % table->nr_philo);

}

void	ft_unlock_fork(long i, t_table *table)
{
	if (!table || !table->forks)
	{
		printf("Error: table or forks is NULL\n");
		return;
	}
	pthread_mutex_unlock(&table->forks[i].fork);
	pthread_mutex_unlock(&table->forks[(i + 1) % table->nr_philo].fork);
	printf("Philo %d has released forks %ld and %ld\n", \
				table->philos[i].philo_id, i, (i + 1) % table->nr_philo);
}
