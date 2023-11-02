#include "../includes/philo.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

void	print_action(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->sim->msg_mutex);
	printf("%ld %d %s", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo->philo_id + 1, msg);
	pthread_mutex_unlock(&philo->sim->msg_mutex);
}

int8_t	philo_sleep(t_philo *philo)
{
		if (simulation_should_stop(philo->sim, NULL, NULL))
			return (-1);
		else
		{
			print_action(philo, "is sleeping\n");
			ft_usleep(philo->sim->time_to_sleep * 1000);
		}
		if (simulation_should_stop(philo->sim, NULL, NULL))
			return (-1);
		return (1);
}

int8_t	philo_think(t_philo *philo)
{
		if (simulation_should_stop(philo->sim, NULL, NULL))
			return (-1);
		else
			print_action(philo, "is thinking\n");
		return (1);
}

int8_t	philo_eat(t_philo *philo)
{
	return (philo->eat_func(philo));
}
