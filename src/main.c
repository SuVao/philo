#include "../inc/philosophers.h"

// void* sub(void* av)
// {
// 	int* arr = malloc(50 * sizeof(int));
// 	arr = (int*)av;
// 	printf("res do sub: %d \n", arr[0] - arr[1]);
// 	return NULL;
// }

// void*  sum(void* av)
// {
// 	int* arr = malloc(50 * sizeof(int));
// 	arr = (int*)av;
// 	printf("res do sum: %d \n", arr[0] + arr[1]);
// 	free(arr);
// 	return NULL;
// }

// int	main(int ac, char **av)
// {
// 	pthread_t	th[2];
// 	int a, b;
// 	(void)ac;
// 	a = atoi(av[1]);
// 	b = atoi(av[2]);
// 	int arr[2];
// 	arr[0] = a;
// 	arr[1] = b;

// 	int i = 0;
// 	while (i < 2)
// 	{
// 		if (i == 1)
// 		{
// 			if (pthread_create(&th[i], NULL, &sum, arr) != 0)
// 				perror("fail to create");
// 		}
// 		else
// 		{
// 			if (pthread_create(&th[i], NULL, &sub, arr) != 0)
// 				perror("fail to create");
// 		}
// 	}
// 	i = 0;
// 	while (i < 2)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			perror("fail to join");
// 	}
// }



// int 	main(int ac, char **av)
// {
// 	if (ac == 6)
// 	{
// 		int nr_philo = atoi(av[1]);
// 		init_threads(nr_philo, eat, die, sleep);
// 	}

// }

// void* routine()
// {
// 	printf("teste from threads\n");
// 	sleep(3);
// 	printf("ending\n");
// }

// void* routine2()
// {
// 	int a, b;
// 	a = 1;
// 	b = 2;
// 	printf("res: %d\n", a + b);
// }

// int main(int ac, char **av)
// {
// 	(void)av;
// 	(void)ac;
// 	pthread_t	t1, t2;
// 	pthread_create(&t1, NULL, &routine, NULL);
// 	pthread_create(&t2, NULL, &routine2, NULL);
// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// 	return (0);
// }

t_philo	*main_philo(void)
{
	static t_philo philo;
	return (&philo);
}

t_table	*main_table(void)
{
	static t_table	table;
	return (&table);
}

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

void	init_philo(char **av)
{
	if (check_args(av) == 1)
	{
		printf("Error: wrong arguments\n");
		return ;
	}
	main_philo()->nr_philo = ft_atol(av[1]);
}

void	lets_the_party_begins(void)
{

}

void	puting_the_forks_on_the_table(void)
{
	int i;

	i = 0;
	while (main_philo()->nr_philo > i)
	{

	}
}

void	init_philo_opc(char **av)
{
	if (check_args(av) == 1)
	{
		printf("Error: wrong arguments\n");
		return ;
	}
	main_philo()->nr_philo = ft_atol(av[1]);
	main_table()->time_to_die = ft_atol(av[2]);
	main_table()->time_to_eat = ft_atol(av[3]);
	main_table()->time_to_sleep = ft_atol(av[4]);
	main_table()->nb_of_meals = ft_atol(av[5]);
	printf("nr philos: %ld\n", main_philo()->nr_philo);
	printf("nr philos: %ld\n", main_table()->time_to_die);
	printf("nr philos: %ld\n", main_table()->time_to_eat);
	printf("nr philos: %ld\n", main_table()->time_to_sleep);
	printf("nr philos: %ld\n", main_table()->nb_of_meals);
	puting_the_forks_on_the_table();

	//lets_the_party_begins();
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
