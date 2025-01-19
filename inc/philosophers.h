#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_table t_table;
typedef struct s_monitor t_monitor;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}				t_fork;

typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
}				t_code;

typedef struct s_philo
{
	int				philo_id;
	long			last_meal_time;
	long			meal_count;
	long			nb_philo_meals;
	bool            full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_table			*table;
	t_monitor		*monitor;
	pthread_mutex_t	philo_mute;
	bool			sync_phi;
	bool            dead;
}					t_philo;

typedef struct s_table
{
	pthread_mutex_t	table_mute;
	bool			sync;
	bool			stop_simulation;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nr_philo;
	long			nb_of_meals;
	long            philo_seated;
	t_fork			*forks;
	t_philo			*philos;
	int				shared_fork;
	t_monitor		*monitor;
}				t_table;

typedef struct s_monitor
{
	pthread_t		monitor_thread;
	pthread_mutex_t	monitor_mute;
	t_table			*table;
	t_philo			*philo;
	bool			death;
	long			meal_count;
}				t_monitor;

//init_threads
void	ft_create_thread(t_table *table);
void	ft_lock_threads(t_table *table);
void	ft_unlock_threads(t_table *table);
void	ft_thread_join(t_table *table);

//dinner
void	*dog_life(void *philo1);
void	mutex_threads(t_table *table, t_philo *philo);
void	ft_lock_fork(long i, t_table *table);
void	ft_unlock_fork(long i, t_table *table);
void	ft_sync_threads(t_table *table);
void	ft_mutex_handler(pthread_mutex_t *mutex, t_code code);

//checks
bool	ft_check_time(t_table *table);

//cleaning_house
void	washing_dishes(t_table *table);
void	kickoff_the_clients(t_table *table);

//philo
void 	*simulation_monitor(void *arg);
void	table_for_pair_philos(t_table *table);
void	table_for_odd_philos(t_table *table);
void	init_philo_opc(char **av);

//math_utils
long ft_atol(char *s);
int is_digit(char c);
long get_current_time(t_table *table);
int	ft_usleep(long milliseconds, t_table *table);

//utils
int check_args(char **av);
void	print_philo_data(long i, t_table *table);
bool	ft_check_philo_nr(t_table *table);
void	init_table(char **av, t_table **table);

//init_table
t_philo	create_philo(t_philo *philos, long i, t_table *table);
t_fork	create_forks(t_fork *forks_table, long i, t_table *table);
void	puting_the_forks_on_the_table(t_table *table, t_fork **forks_table);
void	seating_the_gentlemans(t_table *table, t_philo **philo);

int	ft_timez(long eat, long sleep, long die);
void	*monitor_routine(void *gamela);
void create_monitor(t_monitor **monitor, t_table *table);

//get_and_set
void	ft_set_bool(pthread_mutex_t *mutex, bool *des, bool val);
bool	ft_get_bool( pthread_mutex_t *mutex, bool *val);
long	ft_get_long(pthread_mutex_t *mutex, long *val);
void	ft_set_long(pthread_mutex_t *mutex, long *des, long val);

void ft_eat_routine(t_philo *philo);
void    ft_philo_thinks(t_philo *philo);
void    ft_one_more_seated(pthread_mutex_t *mutex, long *philo_seated);
bool    all_philo_seats(pthread_mutex_t *mutex, long *philos, long philo_nr);

bool    found_dead_philo(t_philo *philo);

#endif
