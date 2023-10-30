#include "../includes/philo.h"
#include "../libft/libft.h"
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static bool	philo_is_dead(t_philo *philo)
{
	int64_t	time_ellapsed;

	time_ellapsed = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	time_ellapsed = time_ellapsed_in_ms(philo->last_meal, get_time());
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_ellapsed >= philo->sim->time_to_die)
	{
		print_action(philo, "died\n");
		if (philo->sim->number_of_philosophers == 1)
		{
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
		}
		return (true);
	}
	return (false);
}

static bool	all_philos_are_full(t_simulation *sim)
{
	int16_t	i;
	
	i = 0;
	while (i < sim->number_of_philosophers)
	{
		if (sim->philo[i].is_full == false)
			return (false);
		i++;
	}
	return (true);
}

static	void	terminate_simulation(t_simulation *sim)
{
	pthread_mutex_lock(&sim->state_mutex);
	sim->terminate = true;
	pthread_mutex_unlock(&sim->state_mutex);
}

void	monitor_routine(t_simulation *sim)
{
	int16_t i;

	i = 0;
	if (sim->number_of_times_each_philosopher_must_eat > 0)
	{
		while (1)
		{
			if (philo_is_dead(&sim->philo[i]) || all_philos_are_full(sim))
				break ;
			i++;
			if (i >= sim->number_of_philosophers)
				i = 0;
		}
	}
	else
	{
		while (1)
		{
			if (philo_is_dead(&sim->philo[i]))
				break ;
			i++;
			if (i >= sim->number_of_philosophers)
				i = 0;
		}
	}
	terminate_simulation(sim);
}
