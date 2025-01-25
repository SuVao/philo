#include "../inc/philosophers.h"

void    ft_philo_thinks(t_philo *philo)
{
    printf_mutex(THINKING, philo);
    if (ft_get_long(&philo->table->table_mute, &philo->table->nr_philo) % 2 == 1)
        ft_usleep(50, philo->table);
}

void    ft_eat_routine(t_philo *philo)
{
    long    meals;
    long    time;

    time = get_current_time(philo->table);
    meals = ft_get_long(&philo->philo_mute, &philo->nb_philo_meals);
    ft_mutex_handler(&philo->left_fork->fork , LOCK);
    printf_mutex(LEFT_FORK, philo);
    ft_mutex_handler(&philo->right_fork->fork , LOCK);
    printf_mutex(RIGHT_FORK, philo);
    ft_set_long(&philo->philo_mute, &philo->last_meal_time, time);
    ft_set_long(&philo->philo_mute, &philo->nb_philo_meals, meals++);
    printf_mutex(EAT, philo);
    ft_usleep(philo->table->time_to_eat, philo->table);
    ft_mutex_handler(&philo->left_fork->fork , UNLOCK);
    ft_mutex_handler(&philo->right_fork->fork , UNLOCK);
    if (ft_get_long(&philo->philo_mute, &philo->table->nb_of_meals) > 0  \
        && philo->nb_philo_meals == philo->table->nb_of_meals)
    {
        printf_mutex(DEAD, philo);
        ft_set_bool(&philo->philo_mute, &philo->full, true);
        ft_set_bool(&philo->philo_mute, &philo->dead, true);
        ft_set_bool(&philo->table->table_mute, &philo->table->stop_simulation, true);
        return ;
    }
}
