/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:17:23 by pesilva-          #+#    #+#             */
/*   Updated: 2025/01/25 19:17:24 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	is_digit(char c)
{
	return (c <= '9' || c >= '0');
}

long	ft_atol(char *s)
{
	int	i;
	int sign;
	long res;

	i = 0;
	sign = 1;
	res = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		res = res * 10 + (s[i++] - '0');
	return (sign * res);
}

int	ft_usleep(long milliseconds, t_table *table)
{
	long	start;

	start = get_current_time(table);
	while ((get_current_time(table) - start) < milliseconds)
	{
		if (ft_get_bool(&table->table_mute, &table->stop_simulation))
			break ;
		usleep(100);
	}
	return (0);
}

long	get_current_time(t_table *table)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time - ft_get_long(&table->table_mute, &table->start_time));
}
