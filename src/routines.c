#include "../inc/philosophers.h"

//void    ft_philo_thinks(t_philo *philo)
//{
//
//}

void ft_eat_routine(t_philo *philo)
{
    ft_mutex_handler(&philo->left_fork->fork , LOCK);
    printf("%ld %d take the left fork %d\n", get_current_time(philo->table),philo->philo_id, philo->left_fork->fork_id);
    ft_mutex_handler(&philo->right_fork->fork , LOCK);
    printf("%ld %d take the right fork %d\n", get_current_time(philo->table), philo->philo_id, philo->right_fork->fork_id);

    ft_set_long(&philo->philo_mute, &philo->last_meal_time, get_current_time(philo->table));
    philo->nb_philo_meals++;
    printf("%ld %d is eating\n", get_current_time(philo->table), philo->philo_id);
    ft_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->nb_of_meals > 0 && philo->nb_philo_meals == philo->table->nb_of_meals)
        ft_set_bool(&philo->philo_mute, &philo->full, true);

    ft_mutex_handler(&philo->left_fork->fork , UNLOCK);
    printf("%ld %d release the left fork %d\n", get_current_time(philo->table), philo->philo_id, philo->left_fork->fork_id);

    ft_mutex_handler(&philo->right_fork->fork , UNLOCK);
    printf("%ld %d release the right fork %d\n", get_current_time(philo->table) ,philo->philo_id, philo->right_fork->fork_id);

}
