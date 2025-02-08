/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:22:34 by pesilva-          #+#    #+#             */
/*   Updated: 2025/02/08 01:07:51 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_set_bool(pthread_mutex_t *mutex, bool *des, bool val)
{
	ft_mutex_handler(mutex, LOCK);
	*des = val;
	ft_mutex_handler(mutex, UNLOCK);
}

bool	ft_get_bool( pthread_mutex_t *mutex, bool *val)
{
	bool	val_ret;

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

void	ft_set_int(pthread_mutex_t *mutex, int *des, int val)
{
	ft_mutex_handler(mutex, LOCK);
	*des = val;
	ft_mutex_handler(mutex, UNLOCK);
}
