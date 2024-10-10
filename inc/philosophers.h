#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_of_meals;
	int				nr_philo;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_philo_data
{
	int				id;


}				t_philo_data;

int ft_atol(char *s);

#endif
