#include "../inc/philosophers.h"

void	init_philo(char **av)
{
	if (check_args(av) == 1)
	{
		printf("Error: wrong arguments\n");
		return ;
	}
	table()->nr_philo = ft_atol(av[1]);
}

t_philo	create_philo(t_philo *philos, long i)
{
	philos[i].philo_id = i;
	philos[i].left_fork = &table()->forks[i];
	philos[i].right_fork = &table()->forks[(i + 1) % table()->nr_philo];
	philos[i].thread_id = i;
	return (philos[i]);
}

t_fork	create_forks(t_fork *forks_table, long i)
{
	forks_table[i].fork_id = i;
	pthread_mutex_init(&forks_table[i].fork, NULL);
	printf("fork is in use: %ld\n", i);
	return (forks_table[i]);
}

void	puting_the_forks_on_the_table(void)
{
	long i;
	t_fork	*forks_table;

	i = 0;
	forks_table = malloc(sizeof(t_fork ) * table()->nr_philo);
	if (!forks_table)
		return ;
	table()->forks = forks_table;
	while (i < table()->nr_philo)
	{
		forks_table[i] = create_forks(forks_table, i);
	//	printf("Fork %ld created\n", i);
		i++;
	}
	i = 0;
	//while (i < table()->nr_philo)
	//{
	//	printf("id forks: %d\n", forks_table[i].fork_id);
	//	i++;
	//}
}

void	seating_the_gentlemans(void)
{
	long	i;
	t_philo *philos;

	philos = malloc(sizeof(t_philo) * table()->nr_philo);
	table()->philos = philos;
	if (!philos)
	{
		washing_dishes();
		return ;
	}
	i = 0;
	while (i < table()->nr_philo)
	{
		philos[i] = create_philo(philos, i);
		i++;
	}
	//i = 0;
	//while (i < table()->nr_philo)
	//{
	//	print_philo_data(i);
	//	i++;
	//}
}
