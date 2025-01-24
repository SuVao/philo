#include "../inc/philosophers.h"

void	ft_set_bool(pthread_mutex_t *mutex, bool *des, bool val)
{
	ft_mutex_handler(mutex, LOCK);
	*des = val;
	ft_mutex_handler(mutex, UNLOCK);
}

bool	ft_get_bool( pthread_mutex_t *mutex, bool *val)
{
	bool val_ret;

	ft_mutex_handler(mutex, LOCK);
	val_ret = *val;
	ft_mutex_handler(mutex, UNLOCK);
	return (val_ret);
}

long	ft_get_long(pthread_mutex_t *mutex, long *val)
{
	long	val_ret;

	ft_mutex_handler(mutex, LOCK);
	val_ret = *val;
	ft_mutex_handler(mutex, UNLOCK);
	return (val_ret);
}

void	ft_set_long(pthread_mutex_t *mutex, long *des, long val)
{
	ft_mutex_handler(mutex, LOCK);
	*des = val;
	ft_mutex_handler(mutex, UNLOCK);
}

int	ft_get_int(pthread_mutex_t *mutex, int *val)
{
	int	val_ret;

	ft_mutex_handler(mutex, LOCK);
	val_ret = *val;
	ft_mutex_handler(mutex, UNLOCK);
	return (val_ret);
}
