#include "../includes/philo.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

long int	time_ellapsed_in_ms(size_t start_time)
{
	struct timeval tv;
	size_t ms_ellapsed;

	gettimeofday(&tv, NULL);
	ms_ellapsed = (tv.tv_usec / 1000) - start_time;
	// printf("ellapsed time in ms: %ld\n", ms_ellapsed);
	return (ms_ellapsed);
}

size_t	start_timer()
{
	struct timeval tv;
	size_t start_time;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_usec / 1000;
	// printf("start_time: %ld\n", start_time);
	return (start_time);
}

// void	state_change_timestamp(t_simulation	*sim)
// {
// 	
// }
