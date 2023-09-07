#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

void	print_time()
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	printf("Seconds elapsed: %ld, microseconds elapsed since last second: %ld\n", current_time.tv_sec, current_time.tv_usec);
}

