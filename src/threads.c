#include "../includes/philo.h"
#include "../libft/libft.h"
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

bool	simulation_should_stop(t_simulation *sim, t_fork *left, t_fork *right)
{
	bool temp_state;

	temp_state = sim->terminate; // to do: add mutex here
	if (temp_state && left)
		pthread_mutex_unlock(left);
	if (temp_state && right)
		pthread_mutex_unlock(right);
	return (temp_state);
}

static void	*routine(void* arg)
{
	t_philo *philo = (t_philo*)arg;
	
	pthread_mutex_lock(&philo->sim->start_mutex);
	pthread_mutex_unlock(&philo->sim->start_mutex);
	while (1)
	{
		if (philo_eat(philo) == -1)
			break ;
		if (philo_sleep(philo) == -1)
			break ;
		philo_think(philo);
	}
	return NULL;
}

int16_t	create_philo_threads(t_simulation *sim)
{
	int16_t	i;

	i = 0;
	pthread_mutex_lock(&sim->start_mutex);
	while (i < sim->number_of_philosophers)
	{
		pthread_mutex_init(&sim->philo[i].meal_mutex, NULL);
		pthread_mutex_init(sim->philo[i].fork_l, NULL);
		pthread_mutex_init(sim->philo[i].fork_r, NULL);
		if (pthread_create(&sim->philo[i].thread, NULL, &routine, &sim->philo[i]) != 0)
			return (ft_putstr_fd("Error creating thread!\n", STDERR_FILENO), -1);
		i++;
	}
	sim->start_time = get_time();
	pthread_mutex_unlock(&sim->start_mutex);
	return (1);
}

int16_t	join_philo_threads(t_simulation *sim)
{
	int16_t	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		if (pthread_join(sim->philo[i].thread, NULL) != 0)
			return (ft_putstr_fd("Error joining thread!\n", STDERR_FILENO), -1);
		pthread_mutex_destroy(&sim->philo[i].meal_mutex);
		pthread_mutex_destroy(sim->philo[i].fork_l);
		pthread_mutex_destroy(sim->philo[i].fork_r);
		i++;
	}
	return (1);
}

static bool	is_philo_dead(t_philo *philo, int16_t philo_id)
{
	int64_t	time_ellapsed;

	time_ellapsed = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	time_ellapsed = time_ellapsed_in_ms(philo->last_meal, get_time());
	time_ellapsed -= philo->sim->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_ellapsed >= philo->sim->time_to_die)
	{
		print_action(philo, "has died\n", philo_id);
		return (true);
	}
	return (false);
}

static bool	is_philo_full(t_philo *philo, int32_t number_of_times_each_philosopher_must_eat)
{
	if (philo->meal_count >= number_of_times_each_philosopher_must_eat)
	{
		print_action(philo, "has finished eating\n", philo->philo_id);
		philo->is_full = true;
		return (true);
	}
	else
		return (false);
}

void	monitor_routine(t_simulation *sim) // Make sure program terminates as soon all philosophers have finished
{
	int16_t i;
	int16_t j;

	i = 0;
	j = 0;
	while (1)
	{
		if (is_philo_dead(&sim->philo[i], i))
			break ;
		if (is_philo_full(&sim->philo[i], sim->number_of_times_each_philosopher_must_eat))
			j++;
		if (j == sim->number_of_philosophers)
			break ;
		i++;
		if (i >= sim->number_of_philosophers)
		{
			i = 0;
			j = 0;
		}
	}
	pthread_mutex_lock(&sim->state_mutex);
	sim->terminate = true;
	pthread_mutex_unlock(&sim->state_mutex);
}
