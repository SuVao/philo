#include "../inc/philosophers.h"
#include <pthread.h>

void	*monitor_routine(void *gamela)
{
	t_monitor *monitor;

	monitor = (t_monitor *)gamela;
	while (!ft_get_bool(&monitor->monitor_mute, &monitor->death))
	{
		//printf("%d\n", monitor->death);
	//	printf("ola\n");
		ft_set_bool(&monitor->monitor_mute, &monitor->death, true);

	}
	return (NULL);
}

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
	if (pthread_create(&table->monitor->monitor_thread, NULL, &monitor_routine, &table->monitor) != 0)
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
	if (pthread_join(table->monitor->monitor_thread, NULL) != 0)
	{
		printf("Error: failed to join thread\n");
		return ;
	}
}
