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

void	lets_the_party_begins(void)
{

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
		printf("Fork %ld created\n", i);
		i++;
	}
	i = 0;
	while (i < table()->nr_philo)
	{
		printf("id forks: %d\n", forks_table[i].fork_id);
		i++;
	}
}

void	seating_the_gentlemans()
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
	i = 0;
	while (i < table()->nr_philo)
	{
		print_philo_data(i);
		i++;
	}
}

void	init_philo_opc(char **av)
{
	if (check_args(av) == 1)
	{
		printf("Error: wrong arguments\n");
		return ;
	}
	init_table(av);
	puting_the_forks_on_the_table();
	seating_the_gentlemans();
	//lets_the_party_begins();
	washing_dishes();
	kickoff_the_clients();
}

int main(int ac, char **av)
{
	if (ac == 6)
		init_philo_opc(av);
	else if (ac == 5)
		init_philo(av)	;
	else
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
}
