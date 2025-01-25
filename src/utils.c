#include "../inc/philosophers.h"

int check_args(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

bool	ft_check_philo_nr(t_table *table)
{
	if (table->nr_philo == 1)
	{
		printf("the philo is dead\n");
		return (false);
	}
	else if (table->nr_philo < 1)
	{
		printf("Invalid nunber of philos\n");
		return (false);
	}
	return (true);
}

int	ft_timez(long eat, long sleep, long die)
{
	if (eat <= 1)
		return (0);
	if (sleep <= 1)
		return (0);
	if (die <= 1)
		return (0);
	return (1);
}

void	init_table(char **av, t_table **table)
{
    *table = malloc(sizeof(t_table));
    if (!(*table))
    {
        printf("Error: memory allocation failed\n");
        return ;
    }
    (*table)->sync = false;
    ft_mutex_handler(&(*table)->table_mute, INIT);
    ft_mutex_handler(&(*table)->print, INIT);

    (*table)->stop_simulation = false;
    (*table)->nr_philo = ft_atol(av[1]);
    (*table)->time_to_die = ft_atol(av[2]);
    (*table)->time_to_eat = ft_atol(av[3]);
    (*table)->time_to_sleep = ft_atol(av[4]);
    (*table)->philo_seated = 0;
    (*table)->start_time = 0;
    if (!ft_timez(ft_atol(av[2]), ft_atol(av[3]), ft_atol(av[4])))
    	return ;
    if (av[5] == NULL)
        (*table)->nb_of_meals = LLONG_MAX;
    else if (ft_atol(av[5]) == 0)
    	return ;
    else
        (*table)->nb_of_meals = ft_atol(av[5]);

}

void    printf_mutex(t_printf_mutex status, t_philo *philo)
{
    long time;

    time = get_current_time(philo->table);
    if (philo->full)
        return ;
    //write(1, "ola\n", 5);
    //printf("full: %b\n", philo->full);
    ft_mutex_handler(&philo->table->print, LOCK);
   // write(1, "ola1\n", 6);

    if ((LEFT_FORK == status || RIGHT_FORK == status) && \
        !ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
        printf("%ld %d take the fork\n", time,\
            ft_get_int(&philo->philo_mute, &philo->philo_id));
    if (EAT == status && \
        !ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
        printf("%ld %d is eating\n", time, ft_get_int(&philo->philo_mute, &philo->philo_id));
    if (SLEEP == status && \
        !ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
        printf("%ld %d is sleeping\n", time, ft_get_int(&philo->philo_mute, &philo->philo_id));
    if (THINKING == status && \
        !ft_get_stop(&philo->table->table_mute, &philo->table->stop_simulation))
        printf("%ld %d is thinking\n", time, ft_get_int(&philo->philo_mute, &philo->philo_id));
    if (DEAD == status)
        printf("%ld philo %d is dead\n", time, ft_get_int(&philo->philo_mute, &philo->philo_id));
    ft_mutex_handler(&philo->table->print, UNLOCK);
  //  write(1, "adeus\n", 7);

}
