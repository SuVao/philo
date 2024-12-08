#include "../inc/philosophers.h"

void	ft_check_time(void)
{
	if (table()->time_to_die < 60)
	{
		printf("Error: time to die must be at least 60\n");
		exit(1);
	}
	if (table()->time_to_eat < 60)
	{
		printf("Error: time to eat must be at least 60\n");
		exit(1);
	}
	if (table()->time_to_sleep < 60)
	{
		printf("Error: time to sleep must be at least 60\n");
		exit(1);
	}
}
