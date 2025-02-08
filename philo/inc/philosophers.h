/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:22:33 by pesilva-          #+#    #+#             */
/*   Updated: 2025/02/08 11:12:49 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_table	t_table;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}				t_fork;

typedef enum e_printfmutex
{
	EAT,
	SLEEP,
	THINKING,
	LEFT_FORK,
	RIGHT_FORK,
	DEAD,
}			t_printf_mutex;

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
	int				meal_count;
	int				nb_philo_meals;
	bool			full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_table			*table;
	pthread_mutex_t	philo_mute;
	bool			sync_phi;
	bool			is_eat;
}					t_philo;

typedef struct s_table
{
	pthread_mutex_t	table_mute;
	pthread_mutex_t	print;
	bool			sync;
	bool			stop_simulation;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nr_philo;
	int				nb_of_meals;
	int				philo_seated;
	t_fork			*forks;
	t_philo			*philos;
	int				shared_fork;
	pthread_t		monitor;
}				t_table;

//init_threads
void	ft_create_thread(t_table *table);
void	ft_thread_join(t_table *table);

//dinner
void	*dog_life(void *philo1);
void	mutex_threads(t_table *table, t_philo *philo);
void	ft_sync_threads(t_philo *philos);
void	ft_mutex_handler(pthread_mutex_t *mutex, t_code code);

//checks
bool	ft_check_time(t_table *table);

//cleaning_house
void	washing_dishes(t_table *table);
void	kickoff_the_clients(t_table *table);

//philo
void	init_philo_opc(char **av);

//math_utils
long	ft_atol(char *s);
int		is_digit(char c);
long	get_current_time(t_table *table);
int		ft_usleep(long milliseconds, t_table *table);

//utils
int		check_args(char **av);
bool	ft_check_philo_nr(t_table *table);
void	init_table(char **av, t_table **table);
void	printf_mutex(t_printf_mutex status, t_philo *philo);

//init_table
t_philo	create_philo(t_philo *philos, long i, t_table *table);
t_fork	create_forks(t_fork *forks_table, long i);
void	puting_the_forks_on_the_table(t_table *table, t_fork **forks_table);
void	seating_the_gentlemans(t_table *table, t_philo **philo);

int		ft_timez(long eat, long sleep, long die);
void	*monitor_routine(void *gamela);

//get_and_set
void	ft_set_bool(pthread_mutex_t *mutex, bool *des, bool val);
bool	ft_get_bool( pthread_mutex_t *mutex, bool *val);
long	ft_get_long(pthread_mutex_t *mutex, long *val);
void	ft_set_int(pthread_mutex_t *mutex, int *des, int val);
int		ft_get_int(pthread_mutex_t *mutex, int *val);
void	ft_set_long(pthread_mutex_t *mutex, long *des, long val);
void	ft_philo_thinks(t_philo *philo);

void	ft_eat_routine(t_philo *philo);
void	ft_one_more_seated(pthread_mutex_t *mutex, int *philo_seated);
bool	all_philo_seats(pthread_mutex_t *mutex, int philos, int philo_nb);
bool	found_dead_philo(t_philo *philo);
void	ft_set_stop(pthread_mutex_t *mutex, bool *stop, bool val);
bool	ft_get_stop(pthread_mutex_t *mutex, bool *stop);
bool	check_av(char **av);
bool	all_full(t_philo *philo);
bool	check_gamela(t_table *table, int i);
void	ft_think(t_philo *philo, long time);
void	print_one_dead(char **av);

#endif
