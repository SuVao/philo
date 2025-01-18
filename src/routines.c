#include "../inc/philosophers.h"

void ft_eat_routine(t_philo *philo)
{
    ft_mutex_handler(&philo->left_fork->fork , LOCK);
    ft_mutex_handler(&philo->right_fork->fork , LOCK);

    ft_set_long(&philo->philo_mute, &philo->last_meal_time, get_current_time(philo->table));

   // ft_usleep(philo->table->time_to_eat, philo->table);


    ft_mutex_handler(&philo->left_fork->fork , UNLOCK);
    ft_mutex_handler(&philo->right_fork->fork , UNLOCK);
}
