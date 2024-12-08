#include "../inc/philosophers.h"

int is_digit(char c)
{
	return (c <= '9' || c >= '0');
}

long ft_atol(char *s)
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
