#include "../inc/philosophers.h"

void	ft_check_time(t_table *table)
{
	if (table->time_to_die < 59)
	{
		printf("Error: time to die must be at least 60\n");
		exit(1);
	}
	if (table->time_to_eat < 59)
	{
		printf("Error: time to eat must be at least 60\n");
		exit(1);
	}
	if (table->time_to_sleep < 59)
	{
		printf("Error: time to sleep must be at least 60\n");
		exit(1);
	}
}
