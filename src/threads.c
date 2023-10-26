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

	pthread_mutex_lock(&sim->state_mutex);
	temp_state = sim->terminate;
	pthread_mutex_unlock(&sim->state_mutex);
	if (temp_state && left)
		pthread_mutex_unlock(left);
	if (temp_state && right)
		pthread_mutex_unlock(right);
	return (temp_state);
}

static void	*routine(void* arg)
{
	t_philo *philo = (t_philo*)arg;
	if (philo->philo_id % 2 == 0)
		philo->eat_func = &philo_eat_even;
	else
	 	philo->eat_func = &philo_eat_even;
	
	pthread_mutex_lock(&philo->sim->start_sim_mutex);
	pthread_mutex_unlock(&philo->sim->start_sim_mutex);
	if (philo->philo_id % 2 == 0)
		ft_usleep((philo->sim->time_to_eat) * 500);
	while (1)
	{
		if (philo_eat(philo) == -1)
			break ;
		if (philo_sleep(philo) == -1)
			break ;
		if (philo_think(philo) == -1)
			break ;
	}
	return NULL;
}

int16_t	create_philo_threads(t_simulation *sim)
{
	int16_t	i;

	i = 0;
	pthread_mutex_lock(&sim->start_sim_mutex);
	while (i < sim->number_of_philosophers)
	{
		pthread_mutex_init(&sim->philo[i].meal_mutex, NULL);
		pthread_mutex_init(&sim->philo[i].state_mutex, NULL);
		pthread_mutex_init(sim->philo[i].fork_l, NULL);
		pthread_mutex_init(sim->philo[i].fork_r, NULL);
		if (pthread_create(&sim->philo[i].thread, NULL, &routine, &sim->philo[i]) != 0)
			return (ft_putstr_fd("Error creating thread!\n", STDERR_FILENO), -1);
		i++;
	}
	sim->start_time = get_time();
	i = 0;
	while (i < sim->number_of_philosophers)
	{
		sim->philo[i].last_meal = sim->start_time;
		i++;
	}
	pthread_mutex_unlock(&sim->start_sim_mutex);
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
		pthread_mutex_destroy(&sim->philo[i].state_mutex);
		pthread_mutex_destroy(sim->philo[i].fork_l);
		pthread_mutex_destroy(sim->philo[i].fork_r);
		i++;
	}
	return (1);
}
