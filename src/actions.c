#include "../includes/philo.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

static int16_t	philo_odd(t_philo *philo)
{
		if (simulation_should_stop(philo->sim, NULL, NULL))
			return (-1);
		pthread_mutex_lock(philo->fork_l);
				printf("%ld %d has taken a fork\n", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo->philo_id + 1);
		if (simulation_should_stop(philo->sim, philo->fork_l, NULL))
			return (-1);
		pthread_mutex_lock(philo->fork_r);
		if (simulation_should_stop(philo->sim, philo->fork_l, philo->fork_r))
			return (-1);
		printf("%ld %d is eating\n", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo->philo_id + 1);
		usleep(philo->sim->time_to_eat * 1000);
		philo->meal_count++;
		if (simulation_should_stop(philo->sim, philo->fork_l, philo->fork_r))
			return (-1);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return (1);	
}

static int16_t	philo_even(t_philo *philo)
{
		if (simulation_should_stop(philo->sim, NULL, NULL))
			return (-1);
		pthread_mutex_lock(philo->fork_r);
				printf("%ld %d has taken a fork\n", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo->philo_id + 1);
		if (simulation_should_stop(philo->sim, NULL, philo->fork_r))
			return (-1);
		pthread_mutex_lock(philo->fork_l);
		if (simulation_should_stop(philo->sim, philo->fork_l, philo->fork_r))
			return (-1);
		printf("%ld %d has taken a fork\n", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo->philo_id + 1);

		printf("%ld %d is eating\n", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo->philo_id + 1);
		usleep(philo->sim->time_to_eat * 1000);
		philo->meal_count++;
		if (simulation_should_stop(philo->sim, philo->fork_l, philo->fork_r))
			return (-1);
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		return (1);	
}

int16_t	philo_eat(t_philo *philo)
{
		int16_t	err;

		if (philo->philo_id % 2 == 0)
			err = philo_even(philo);
		else
		 	err = philo_odd(philo);
		if (err == -1)
			return (-1);
		else
		{
			pthread_mutex_lock(&philo->meal_mutex);
			philo->last_meal = get_time();
			pthread_mutex_unlock(&philo->meal_mutex);
			return (1);
		}
}

int16_t	philo_sleep(t_philo *philo)
{
		printf("%ld %d is sleeping\n", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo->philo_id + 1);
		usleep(philo->sim->time_to_sleep * 1000);
		if (simulation_should_stop(philo->sim, NULL, NULL))
			return (-1);
		return (1);
}

void	philo_think(t_philo *philo)
{
		printf("%ld %d is thinking\n", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo->philo_id + 1);
}

