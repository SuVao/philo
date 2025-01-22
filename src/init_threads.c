#include "../inc/philosophers.h"

void	ft_create_thread(t_table *table)
{
	long i;
	i = 0;
	while (i < table->nr_philo)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &dog_life, &table->philos[i]) != 0)
		{
			printf("Error: failed to create thread\n");
			return ;
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &monitor_routine, table) != 0)
	{
		printf("Error: failed to create the monitor");
		return ;
	}
}

void	ft_lock_threads(t_table *table)
{
	long i;

	i = 0;
	while (i < table->nr_philo)
	{
		ft_mutex_handler(&table->forks[i].fork, LOCK);
		i++;
	}
	//ft_mutex_handler(&table->monitor->monitor_mute, LOCK);
	//ft_mutex_handler(&table->table_mute, LOCK);

}

void	ft_unlock_threads(t_table *table)
{
	long i;

	i = 0;
	while (i < table->nr_philo)
	{
		ft_mutex_handler(&table->forks[i].fork, UNLOCK);
		i++;
	}
	//ft_mutex_handler(&table->monitor->monitor_mute, UNLOCK);
	//ft_mutex_handler(&table->table_mute, UNLOCK);
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
			return ;
		}
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 0)
	{
		printf("Error: failed to join thread\n");
		return ;
	}
}
