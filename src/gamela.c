#include "../inc/philosophers.h"

void create_monitor(t_monitor **monitor, t_table *table)
{
	(*monitor) = malloc(sizeof(t_monitor));
	if (!monitor)
		return ;
	(*monitor)->monitor_thread = 2;
	(*monitor)->death = false;
	(*monitor)->meal_count = 0;
	(*monitor)->table = table;
	ft_mutex_handler(&(*monitor)->monitor_mute, INIT);
}

void    found_dead_philo()

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
		    if (found_dead_philo())
		    i++;
		}
		ft_set_bool(&table->monitor->monitor_mute, &table->monitor->death, true);
	}
	return (NULL);
}
