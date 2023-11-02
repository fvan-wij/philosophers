#include "../includes/philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int8_t	print_action(t_philo *philo, const char *msg) //Check if sim should stop
{
	bool	temp;

	temp = false;
	pthread_mutex_lock(&philo->sim->term_mutex);
	temp = philo->sim->terminate;
	pthread_mutex_unlock(&philo->sim->term_mutex);
	if (temp)
		return (-1);
	else
	{
		pthread_mutex_lock(&philo->sim->msg_mutex);
		printf("%ld %d %s", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo->philo_id, msg);
		pthread_mutex_unlock(&philo->sim->msg_mutex);
		return (1);
	}
}

int8_t	philo_eat(t_philo *philo)
{
	return (philo->eat_func(philo));
}

int8_t	philo_sleep(t_philo *philo)
{
	if (print_action(philo, "is sleeping\n") == -1)
		return (-1);
	ft_usleep(MS(philo->sim->time_to_sleep));
	return (1);
}

int8_t	philo_think(t_philo *philo)
{
		if (print_action(philo, "is thinking\n") == -1)
			return (-1);
		return (1);
}
