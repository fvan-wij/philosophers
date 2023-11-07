#include "../includes/philo.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

int64_t	time_elapsed_in_ms(int64_t start_time, int64_t end_time)
{
	int64_t delta_time;
	delta_time = end_time - start_time;
	return (delta_time);
}

int64_t	get_time()
{
	struct 	timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int8_t	ft_usleep(int64_t usec)
{
	int64_t	wake_up_time;
	int8_t	err;

	wake_up_time = get_time() + usec / 1000;
	err = 0;
	while (get_time() <= wake_up_time)
		err = usleep(250);
	return (err);
}
