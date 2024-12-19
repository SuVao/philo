#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_table t_table;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}				t_fork;

typedef struct s_philo
{
	int				philo_id;
	long			last_meal;
	long			meal_count;
	int				nb_of_meals;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_table			*table;
}					t_philo;

typedef struct s_table
{
	int				dead;
	int				stop_simulation;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nr_philo;
	long			nb_of_meals;
	t_fork			*forks;
	t_philo			*philos;
	int				shared_fork;
}				t_table;

//init_threads
void	ft_create_thread(t_table *table);
void	ft_lock_threads(t_table *table);
void	ft_unlock_threads(t_table *table);
void	ft_thread_join(t_table *table);

//dinner
void	*dog_life(void *table);
void	ft_lock_fork(long i, t_table *table);
void	ft_unlock_fork(long i, t_table *table);

//checks
void	ft_check_time(t_table *table);

//cleaning_house
void	washing_dishes(t_table *table);
void	kickoff_the_clients(t_table *table);

//philo
void 	*simulation_monitor(void *arg);
void	table_for_pair_philos(t_table *table);
void	table_for_odd_philos(t_table *table);
void	mutex_threads(t_table *table);
void	init_philo_opc(char **av);

//math_utils
long ft_atol(char *s);
int is_digit(char c);
long get_current_time(t_table *table);
int	ft_usleep(long milliseconds, t_table *table);

//utils
int check_args(char **av);
void	print_philo_data(long i, t_table *table);
void	ft_check_philo_nr(t_table *table);
void	init_table(char **av, t_table **table);

//init_table
t_philo	create_philo(t_philo *philos, long i, t_table *table);
t_fork	create_forks(t_fork *forks_table, long i, t_table *table);
void	puting_the_forks_on_the_table(t_table *table, t_fork **forks_table);
void	seating_the_gentlemans(t_table *table, t_philo **philo);

#endif
