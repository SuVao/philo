#include "../inc/philosophers.h"

void create_monitor(t_monitor **monitor, t_table *table)
{
	(*monitor) = malloc(sizeof(t_monitor));
	if (!monitor)
		return ;
	(*monitor)->monitor_thread = 0;
	(*monitor)->death = false;
	(*monitor)->meal_count = 0;
	(*monitor)->table = &table;
	ft_mutex_handler(&(*monitor)->monitor_mute, INIT);
}

bool    found_dead_philo(t_philo *philo)
{
    long t_die;
    long time;

    if (ft_get_bool(&philo->philo_mute, &philo->full))
        return (false);

    time = get_current_time(philo->table) - \
            ft_get_long(&philo->philo_mute, &philo->last_meal_time);
    t_die = philo->table->time_to_die;
    if (time > t_die)
        return (true);
    return (false);
}

bool    all_philo_seats(pthread_mutex_t *mutex, long *philos, long philo_nr)
{
    bool    ola;

    ola = false;
    ft_mutex_handler(mutex, LOCK);
    if (*philos == philo_nr)
        ola = true;
    ft_mutex_handler(mutex, UNLOCK);
    return (ola);
}

void	*monitor_routine(void *table1)
{
    int         i;
    t_table     *table;

	table = (t_table *)table1;
	while (!all_philo_seats(&table->table_mute, &table->philo_seated, table->nr_philo))
	   ;
	while (!ft_get_bool(&table->table_mute, &table->stop_simulation))
	{
	    i = 0;
		while (i < table->nr_philo)
		{
		    if (found_dead_philo(table->philos + i) && \
				!ft_get_bool(&table->table_mute, &table->stop_simulation))
			{
                ft_set_bool(&table->table_mute, &table->stop_simulation, true);
                printf("the philo %d is dead!!!\n", table->philos[i].philo_id);
			}
		    i++;
		}
	//	ft_set_bool(&table->monitor->monitor_mute, &table->monitor->death, true);
	}
	return (NULL);
}
