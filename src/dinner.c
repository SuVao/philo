#include "../inc/philosophers.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
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
	ft_set_bool(&table->table_mute, &table->stop_simulation, true);
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
        //  if (ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
		//   return(NULL);
		//if (philo->full)
		//{
		//    ft_set_stop(&philo->table->table_mute, &philo->table->stop_simulation, true);
		//	break ;
		//}
		ft_eat_routine(philo);
		if (ft_get_bool(&philo->philo_mute, &philo->dead))
		{
		    break ;
		}
		//if (ft_get_bool(&philo->table->table_mute, &philo->table->stop_simulation) )
		//    break ;
		printf_mutex(SLEEP, philo);

		ft_usleep(ft_get_long(&philo->table->table_mute, &philo->table->time_to_sleep), philo->table);
		ft_philo_thinks(philo);
	//	ft_set_bool(&philo->table->table_mute, &philo->table->stop_simulation, true);
	}
	return (NULL);
}
