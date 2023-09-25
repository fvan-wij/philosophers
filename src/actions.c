#include "../includes/philo.h"
#include <stdio.h>
#include <unistd.h>

bool	check_death_state(t_simulation *sim)
{
	bool temp_state;

	pthread_mutex_lock(&sim->state_mutex);
	temp_state = sim->is_dead;
	pthread_mutex_unlock(&sim->state_mutex);
	return (temp_state);
}

int16_t	philo_eat(t_philo *philo)
{
		pthread_mutex_lock(philo->fork_l);
		pthread_mutex_lock(philo->fork_r);
			pthread_mutex_lock(&philo->start_mutex);
			printf("%ld %d has taken a fork\n", time_ellapsed_in_ms(philo->start_time, get_time()), philo->philo_id);
			printf("%ld %d is eating\n", time_ellapsed_in_ms(philo->start_time, get_time()), philo->philo_id);
			usleep(philo->sim->time_to_eat * 1000);
			if (check_death_state(philo->sim))
			{
				pthread_mutex_unlock(philo->fork_l);
				pthread_mutex_unlock(philo->fork_r);
				pthread_mutex_unlock(&philo->start_mutex);
				return (-1);
			}
			pthread_mutex_unlock(&philo->start_mutex);
		pthread_mutex_lock(&philo->meal_mutex);
			philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->meal_mutex);

		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return (1);
}

int16_t	philo_sleep(t_philo *philo)
{
		pthread_mutex_lock(&philo->start_mutex);
			printf("%ld %d is sleeping\n", time_ellapsed_in_ms(philo->start_time, get_time()), philo->philo_id);
		pthread_mutex_unlock(&philo->start_mutex);
		usleep(philo->sim->time_to_sleep * 1000);
		if (check_death_state(philo->sim))
			return (-1);
		return (1);
}

void	philo_think(t_philo *philo)
{
		pthread_mutex_lock(&philo->start_mutex);
			printf("%ld %d is thinking\n", time_ellapsed_in_ms(philo->start_time, get_time()), philo->philo_id);
		pthread_mutex_unlock(&philo->start_mutex);
}

