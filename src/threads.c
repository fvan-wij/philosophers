#include "../includes/philo.h"
#include "../libft/libft.h"
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	*routine(void* arg)
{
	t_philo *philo = (t_philo*)arg;

	if (philo->sim->number_of_philosophers == 1)
		philo->eat_func = &singular_eat_routine;
	else
		philo->eat_func = &plural_eat_routine;
	pthread_mutex_lock(&philo->sim->start_sim_mutex);
	pthread_mutex_unlock(&philo->sim->start_sim_mutex);
	if (philo->id % 2 != 0)
		ft_sleep((philo->sim->time_to_eat) / 2);
	while (1)
	{
		if (philo_eat(philo) == -1)
			break ;
		if (philo_sleep(philo) == -1)
			break ;
		if (philo_think(philo) == -1)
			break ;
	}
	return (NULL);
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
			return (ft_putstr_fd("Error: thread creation failed!\n", STDERR_FILENO), -1);
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
			return (ft_putstr_fd("Error: could not join thread!\n", STDERR_FILENO), -1);
		i++;
	}
	i = 0;
	while (i < sim->number_of_philosophers)
	{
		pthread_mutex_destroy(&sim->philo[i].meal_mutex);
		pthread_mutex_destroy(&sim->philo[i].state_mutex);
		pthread_mutex_destroy(sim->philo[i].fork_l);
		pthread_mutex_destroy(sim->philo[i].fork_r);
		i++;
	}
	return (1);
}
