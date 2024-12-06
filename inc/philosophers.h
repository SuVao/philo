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
	long			nr_philo;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_table			*table;
}					t_philo;

typedef struct s_table
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nr_philo;
	long			nb_of_meals;
	t_fork			*forks;
	t_philo			*philos;
}				t_table;

int ft_atol(char *s);
int is_digit(char c);


#endif
