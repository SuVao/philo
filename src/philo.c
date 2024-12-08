#include "../inc/philosophers.h"


void	table_for_pair_philos(long i)
{
	ft_lock_fork_for_pair(i);
	table()->philos[i].left_fork = &table()->forks[i];
	table()->philos[i].right_fork = &table()->forks[(i + 1) % table()->nr_philo];
	printf("philo %ld is eating\n", i);
	ft_unlock_fork_for_pair(i);

}

void	table_for_odd_philos(long i)
{
	ft_lock_fork_for_odd(i);
	table()->philos[i].left_fork = &table()->forks[(i + 1) % table()->nr_philo];
	table()->philos[i].right_fork = &table()->forks[i];
	printf("philo %ld is eating\n", i);
	ft_unlock_fork_for_odd(i);
}

void	lets_the_party_begins(void)
{
	table()->shared_fork = 0;
	ft_lock_threads();
	table()->shared_fork++;
	ft_unlock_threads();
	ft_create_thread();
	ft_thread_join();
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
	lets_the_party_begins();
	washing_dishes();
	kickoff_the_clients();
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
}
