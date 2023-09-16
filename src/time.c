#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

long int	time_ellapsed_in_ms(suseconds_t init)
{
	struct timeval tv;
	suseconds_t ms_ellapsed;

	gettimeofday(&tv, NULL);
	ms_ellapsed = (tv.tv_usec - init) / 1000;
	printf("ellapsed time in ms: %ld\n", ms_ellapsed);
	return (ms_ellapsed);
}

