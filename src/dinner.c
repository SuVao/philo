#include "../inc/philosophers.h"
#include <bits/pthreadtypes.h>
#include <stdbool.h>

void	mutex_threads(t_table *table, t_philo *philo)
{
	(void)philo;
	table->shared_fork = 0;
	ft_lock_threads(table);
	table->shared_fork++;
	ft_unlock_threads(table);
	ft_create_thread(table);
	ft_set_bool(&table->table_mute, &philo->sync_phi, true);
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
    while (!ft_get_bool(&table->table_mute, &table->philos->sync_phi))
        ;
}

void    ft_one_more_seated(pthread_mutex_t *mutex, long *philo_seated)
{
    ft_mutex_handler(mutex, LOCK);
    (*philo_seated)++;
    ft_mutex_handler(mutex, UNLOCK);
}

void	*dog_life(void *philo1)
{
	t_philo	*philo;

	philo = (t_philo *)philo1;
	ft_sync_threads( philo->table);
	ft_set_long(&philo->philo_mute , &philo->last_meal_time, get_current_time(philo->table));
	ft_one_more_seated(&philo->table->table_mute , &philo->table->philo_seated);
	while (!ft_get_bool(&philo->table->table_mute, &philo->table->stop_simulation))
	{

	    if (philo->full)
			break ;
		ft_eat_routine(philo);
		printf("%b\n", philo->table->stop_simulation);
		//if (ft_get_bool(&philo->table->table_mute, &philo->table->stop_simulation))
		//    break ;
		printf("%ld %d is sleeping\n", get_current_time(philo->table), philo->philo_id);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		ft_philo_thinks(philo);
	//	ft_set_bool(&philo->table->table_mute, &philo->table->stop_simulation, true);
	}
	return (NULL);
}

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
	printf("time:%ld philo id:%d has taken the fork:%ld\n", time, \
			table->philos[i].philo_id, (i + 1) % table->nr_philo);
	ft_mutex_handler(&table->forks[i].fork, LOCK);
	ft_mutex_handler(&table->forks[(i + 1) % table->nr_philo].fork, LOCK);

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
