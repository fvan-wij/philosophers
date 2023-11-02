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

int8_t	philo_eat_even(t_philo *philo)
{
		pthread_mutex_lock(philo->fork_r);
		if (print_action(philo, "has taken a fork\n") == -1)
		{
			pthread_mutex_unlock(philo->fork_r);
			return (-1);
		}
		pthread_mutex_lock(philo->fork_l);
		if (print_action(philo, "has taken a fork\n") == -1)
		{
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
			return (-1);
		}
		if (print_action(philo, "is eating\n") == -1)
		{
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
			return (-1);
		}
		update_last_meal_time(philo);
		ft_usleep(MS(philo->sim->time_to_eat));
		update_meal_count(philo);
		if (philo->sim->number_of_times_each_philosopher_must_eat > 0 && philo->meal_count >= philo->sim->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_lock(&philo->state_mutex);
			philo->is_full = true;
			pthread_mutex_unlock(&philo->state_mutex);
		}
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		return (1);	
}

int8_t	philo_eat_solo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_r);
	if (print_action(philo, "has taken a fork\n") == -1)
	{
		pthread_mutex_unlock(philo->fork_r);
		return (-1);
	}
	pthread_mutex_unlock(philo->fork_r);
	return (1);
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
