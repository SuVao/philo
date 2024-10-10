#include "../inc/philosophers.h"

int ft_atol(char *s)
{
	int	i;
	int sign;
	long res;

	i = 0;
	sign = 1;
	res = 0;
	while ((s[i] < 32))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (sign == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		res = res * 10 + (s[i++] - '0');
	return (sign * res);
}
