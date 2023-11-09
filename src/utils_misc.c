#include "../includes/philo.h"
#include <stdbool.h>
#include <stdio.h>

int8_t	print_action(t_philo *philo, const char *msg)
{
	bool	temp;
	int64_t	time;
	int64_t	elapsed_time;

	pthread_mutex_lock(&philo->sim->term_mutex);
	temp = philo->sim->terminate;
	pthread_mutex_unlock(&philo->sim->term_mutex);
	if (temp)
		return (-1);
	else
	{
		pthread_mutex_lock(&philo->sim->msg_mutex);
		time = get_time();
		elapsed_time = time_ellapsed_in_ms(philo->sim->start_time, time);
		printf("%ld %d %s", elapsed_time, philo->id, msg);
		pthread_mutex_unlock(&philo->sim->msg_mutex);
		return (1);
	}
}
