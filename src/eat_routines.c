#include "../includes/philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

static void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}

static void	update_meal_count(t_philo *philo)
{
	if (philo->sim->number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->meal_mutex);
	}
}

static void poll_if_full(t_philo *philo)
{
	if (philo->sim->number_of_times_each_philosopher_must_eat > 0 && philo->meal_count >= philo->sim->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->state_mutex);
		philo->is_full = true;
		pthread_mutex_unlock(&philo->state_mutex);
	}
}

int8_t	plural_eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_action(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->fork_r);
	print_action(philo, "has taken a fork\n");
	print_action(philo, "is eating\n");
	update_last_meal_time(philo);
	ft_usleep(MS(philo->sim->time_to_eat));
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	update_meal_count(philo);
	poll_if_full(philo);
	return (1);	
}

int8_t	plural_eat_routine_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_r);
	print_action(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->fork_l);
	print_action(philo, "has taken a fork\n");
	print_action(philo, "is eating\n");
	update_last_meal_time(philo);
	ft_usleep(MS(philo->sim->time_to_eat));
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	update_meal_count(philo);
	poll_if_full(philo);
	return (1);	
}

int8_t	plural_eat_routine_even(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_action(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->fork_r);
	print_action(philo, "has taken a fork\n");
	print_action(philo, "is eating\n");
	update_last_meal_time(philo);
	ft_usleep(MS(philo->sim->time_to_eat));
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	update_meal_count(philo);
	poll_if_full(philo);
	return (1);	
}

int8_t	singular_eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_r);
	print_action(philo, "has taken a fork\n");
	pthread_mutex_unlock(philo->fork_r);
	return (1);
}
