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
	time_ellapsed = time_elapsed_in_ms(philo->last_meal, get_time());
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_ellapsed >= philo->sim->time_to_die)
		return (print_action(philo, "died\n"), true);
	return (false);
}

static	void	terminate_simulation(t_simulation *sim)
{
	pthread_mutex_lock(&sim->term_mutex);
	sim->terminate = true;
	pthread_mutex_unlock(&sim->term_mutex);
}

static bool philo_is_full(t_philo *philo)
{
	bool temp = false;

	pthread_mutex_lock(&philo->state_mutex);
	temp = philo->is_full;
	pthread_mutex_unlock(&philo->state_mutex);
	return (temp);
}

void	monitor_routine(t_simulation *sim)
{
	uint8_t i;
	uint8_t count;

	i = 0;
	count = 0;
	if (sim->number_of_times_each_philosopher_must_eat > 0)
	{
		while (ft_usleep(MS(1)) != -1)
		{
			if (philo_is_dead(&sim->philo[i]))
				break ;
			count += philo_is_full(&sim->philo[i]);
			i++;
			if (count == sim->number_of_philosophers)
				break ;
			else if (i >= sim->number_of_philosophers)
			{
				i = 0;
				count = 0;
			}
		}
	}
	else
	{
		while (ft_usleep(MS(1)) != -1)
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
