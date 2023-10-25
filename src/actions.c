#include "../includes/philo.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

void	print_action(t_philo *philo, const char *msg) //Check if sim should stop
{
	pthread_mutex_lock(&philo->sim->msg_mutex);
	printf("%ld %d %s", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo->philo_id + 1, msg);
	pthread_mutex_unlock(&philo->sim->msg_mutex);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}

static int16_t	philo_eat_odd(t_philo *philo)
{
		pthread_mutex_lock(philo->fork_l);
		if (simulation_should_stop(philo->sim, philo->fork_l, NULL))
			return (-1);
		else
			print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->fork_r);
		if (simulation_should_stop(philo->sim, philo->fork_l, philo->fork_r))
			return (-1);
		else
		{
			print_action(philo, "has taken a fork\n");
			print_action(philo, "is eating\n");
		}
		usleep(philo->sim->time_to_eat * 1000);
		philo->meal_count++;
		update_last_meal_time(philo);
		if (philo->meal_count >= philo->sim->number_of_times_each_philosopher_must_eat)
		{
			print_action(philo, "has finished eating\n");
			philo->is_full = true;
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
			return (1);
		}
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return (1);	
}

static int16_t	philo_eat_even(t_philo *philo)
{
		pthread_mutex_lock(philo->fork_r);
		if (simulation_should_stop(philo->sim, NULL, philo->fork_r))
			return (-1);
		else
			print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->fork_l);
		if (simulation_should_stop(philo->sim, philo->fork_l, philo->fork_r))
			return (-1);
		else
		{
			print_action(philo, "has taken a fork\n");
			print_action(philo, "is eating\n");
		}
		usleep(philo->sim->time_to_eat * 1000); // --> Create a function that loops small amounts of micro sleeps until it should stop sleeping.
		philo->meal_count++;
		update_last_meal_time(philo);
		if (philo->meal_count >= philo->sim->number_of_times_each_philosopher_must_eat)
		{
			print_action(philo, "has finished eating\n");
			philo->is_full = true;
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
			return (1);
		}
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		return (1);	
}


int16_t	philo_eat(t_philo *philo)
{
		if (philo->is_full)
			return (0);
		if (philo->philo_id % 2 == 0)
			return (philo_eat_even(philo));
		else
		 	return (philo_eat_odd(philo));
}

int16_t	philo_sleep(t_philo *philo)
{
		if (simulation_should_stop(philo->sim, NULL, NULL))
			return (-1);
		else
		{
			print_action(philo, "is sleeping\n");
			usleep(philo->sim->time_to_sleep * 1000);
		}
		if (simulation_should_stop(philo->sim, NULL, NULL))
			return (-1);
		return (1);
}

int16_t	philo_think(t_philo *philo)
{
		if (simulation_should_stop(philo->sim, NULL, NULL))
			return (-1);
		else
			print_action(philo, "is thinking\n");
		return (1);
}

