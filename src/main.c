#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

int	main(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	long int init = current_time.tv_usec;
	usleep(1000);
	gettimeofday(&current_time, NULL);
	long int last = current_time.tv_usec;
	printf("time: %ld\n", last - init);
	return (0);
}
