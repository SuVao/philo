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

void	print_philo_data(long i, t_table *table)
{
	printf("philo id: %d\n", table->philos[i].philo_id);
	printf("philo left_fork: %d\n", table->philos[(i + 1) % table->nr_philo].philo_id);
	printf("philo right_fork: %d\n", table->philos[i].philo_id);
	printf("philo thread_id: %lu\n", table->philos[i].thread_id);
}

void	ft_check_philo_nr(t_table *table)
{
	if (table->nr_philo == 1)
	{
		printf("the philo is dead\n");
		return ;
	}
	else if (table->nr_philo < 1)
	{
		printf("Invalid nunber of philos\n");
		return ;
	}
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
    (*table)->stop_simulation = false;
    (*table)->nr_philo = ft_atol(av[1]);
    ft_check_philo_nr(*table);
    (*table)->time_to_die = ft_atol(av[2]);
    (*table)->time_to_eat = ft_atol(av[3]);
    (*table)->time_to_sleep = ft_atol(av[4]);
    ft_check_time(*table);
    if (!ft_timez(ft_atol(av[2]), ft_atol(av[3]), ft_atol(av[4])))
    	return ;
    if (av[5] == NULL)
        (*table)->nb_of_meals = LLONG_MAX;
    else if (ft_atol(av[5]) == 0)
    	return ;
    else
        (*table)->nb_of_meals = ft_atol(av[5]);
    (*table)->philo_seated = 0;
    printf("nr philos: %ld\n", (*table)->nr_philo);
    printf("time to die: %ld\n", (*table)->time_to_die);
    printf("time to eat: %ld\n", (*table)->time_to_eat);
    printf("time to sleep: %ld\n", (*table)->time_to_sleep);
    printf("nbr of meals: %ld\n", (*table)->nb_of_meals);
}
