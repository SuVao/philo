#include "../inc/philosophers.h"
#include <bits/pthreadtypes.h>
#include <stdlib.h>


// void	table_for_pair_philos(long i, t_table *table)
// {
// 	ft_lock_fork_for_pair(i, table);
// 	table->philos[i].left_fork = &table->forks[i];
// 	table->philos[i].right_fork = &table->forks[(i + 1) % table->nr_philo];
// 	printf("philo %ld is eating\n", i);
// 	ft_unlock_fork_for_pair(i, table);

// }

// void	table_for_odd_philos(long i, t_table *table)
// {
// 	ft_lock_fork_for_odd(i, table);
// 	table->philos[i].left_fork = &table->forks[(i + 1) % table->nr_philo];
// 	table->philos[i].right_fork = &table->forks[i];
// 	printf("philo %ld is eating\n", i);
// 	ft_unlock_fork_for_odd(i, table);
// }

void create_monitor(t_monitor **monitor)
{
	(*monitor) = malloc(sizeof(t_monitor));
	if (!monitor)
		return ;
	(*monitor)->monitor_thread = 2;
	(*monitor)->death = 0;
	(*monitor)->meal_count = 0;
}

void	init_philo_opc(char **av)
{
    t_table     *table;
    t_philo     *philo;
    t_fork      *forks_table;

    table = NULL;
    philo = NULL;
    forks_table = NULL;
	if (check_args(av) == 1)
	{
		printf("Error: wrong arguments\n");
		return ;
	}
	init_table(av, &table);
	if (ft_atol(av[1]) <= 1 || !ft_timez(table->time_to_die, \
		table->time_to_sleep, table->time_to_eat))
	{
		free(table);
		return ;
	}
	table->start_time = get_current_time(table);
	puting_the_forks_on_the_table(table, &forks_table);
	if (forks_table == NULL)
		return ;
	create_monitor(&table->monitor);
	table->philos = philo;
	table->forks = forks_table;
	seating_the_gentlemans(table, &philo);
	mutex_threads(table, philo);
	washing_dishes(table);
	kickoff_the_clients(table);
}

int main(int ac, char **av)
{
	if (ac == 6 || ac == 5)
		init_philo_opc(av);
	else
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	return (0);
}
