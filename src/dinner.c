#include "../inc/philosophers.h"
#include <pthread.h>

void	mutex_threads(t_table *table, t_philo *philo)
{
	(void)philo;
	table->shared_fork = 0;
	ft_lock_threads(table);
	table->shared_fork++;
	ft_unlock_threads(table);
	ft_create_thread(table);
	ft_thread_join(table);
}

void	ft_mutex_handler(pthread_mutex_t *mutex, t_code code)
{
	if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
}

void	ft_sync_threads(t_table *table)
{
	long i;

	i = -1;

	return ;
}

void	*dog_life(void *philo1)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo1;
	i = (philo->philo_id - 1);
	ft_sync_threads(philo->table);
	if (philo->table->nr_philo % 2 == 0)
	{
		while (!philo->table->dead)
		{
			if (philo->philo_id % 2 == 0)
			{
				ft_lock_fork(i, philo->table);
				printf("time:%ld philo id:%d is eating\n", get_current_time(philo->table),philo->philo_id);
				ft_usleep(philo->table->time_to_eat, philo->table);
				ft_unlock_fork(i, philo->table);
				printf("time:%ld philo id:%d is sleeping\n", get_current_time(philo->table), philo->philo_id);
			}
			else
			{
				ft_lock_fork(i, philo->table);
				printf("time:%ld philo id:%d is eating\n", get_current_time(philo->table), philo[i].philo_id);
				ft_usleep(philo->table->time_to_eat, philo->table);
				ft_unlock_fork(i, philo->table);
				printf("time: %ld philo id:%d is sleeping\n", get_current_time(philo->table), philo[i].philo_id);
			}
			i = (i + 1) % philo->table->nr_philo;
		}
	}
	else
	{
		while (!philo->table->dead)
		{
			if (philo->philo_id % 2 == 0)
			{
				ft_lock_fork(i, philo->table);
				printf("time:%ld philo id:%d is eating\n", get_current_time(philo->table), philo->philo_id);
				ft_usleep(philo->table->time_to_eat, philo->table);
				ft_unlock_fork(i, philo->table);
				printf("time:%ld philo id:%d is sleeping\n", get_current_time(philo->table), philo->philo_id);
			}
			else
			{
				ft_lock_fork(i, philo->table);
				printf("time:%ld philo id:%d is eating\n", get_current_time(philo->table),philo->philo_id);
				ft_usleep(philo->table->time_to_eat, philo->table);
				ft_unlock_fork(i, philo->table);
				printf("time:%ld philo id:%d is sleeping\n", get_current_time(philo->table), philo->philo_id);
			}
			i = (i + 1) % philo->table->nr_philo;
		}
	}
	return (NULL);
}

// void	*dog_life(void *table1)
// {
// 	t_table    *table;
// 	long i;

// 	i = 0;
// 	table = (t_table *)table1;
// 	//ft_usleep(table->time_to_die);
// 	//sycnronize the threads
// 	//ft_sync_threads(table);
// 	while (!table->dead)
// 	{
// 		if (table->nr_philo % 2 == 0)
// 		{
// 		//	if (philo->)
// 			ft_lock_fork(i, table);
// 			printf("%ld %d is eating\n", get_current_time(table),table->philos[i].philo_id);
// 			ft_usleep(table->time_to_eat, table);
// 			ft_unlock_fork(i, table);
// 			printf("%ld %d is sleeping\n", get_current_time(table), table->philos[i].philo_id);
// 			//ft_usleep(table->time_to_sleep);
// 		//	i = (i + 1) % table->nr_philo;
// 		}
// 		else
// 		{
// 			ft_lock_fork(i, table);
// 			printf("%ld %d is eating\n", get_current_time(table), table->philos[i].philo_id);
// 			ft_usleep(table->time_to_eat, table);
// 			ft_unlock_fork(i, table);
// 			printf("%d is sleeping\n", table->philos[i].philo_id);

// 		}
// 		i = (i + 1) % table->nr_philo;
// 	}
// 	return (NULL);
// }

void	ft_lock_fork(long i, t_table *table)
{
	long	time;

	time = get_current_time(table);
    if (!table || !table->forks)
	{
		printf("Error: table or forks is NULL\n");
		return;
	}
	printf("time:%ld philo id:%ld has taken the fork:%d\n", time, i, table->philos[i].philo_id);
	ft_mutex_handler(&table->forks[i].fork, LOCK);
	ft_mutex_handler(&table->forks[(i + 1) % table->nr_philo].fork, LOCK);
	printf("time:%ld philo id:%d has taken the fork:%ld\n", time, \
			table->philos[i].philo_id, (i + 1) % table->nr_philo);

}

void	ft_unlock_fork(long i, t_table *table)
{
	if (!table || !table->forks)
	{
		printf("Error: table or forks is NULL\n");
		return;
	}
	ft_mutex_handler(&table->forks[i].fork, UNLOCK);
	ft_mutex_handler(&table->forks[(i + 1) % table->nr_philo].fork, UNLOCK);
	printf("%d has released forks %ld and %ld\n", \
				table->philos[i].philo_id, i, (i + 1) % table->nr_philo);
}
