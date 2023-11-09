#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>

int8_t	create_philo_threads(t_simulation *sim)
{
	uint8_t	i;

	i = 0;
	pthread_mutex_lock(&sim->start_sim_mutex);
	while (i < sim->number_of_philosophers)
	{
		pthread_mutex_init(&sim->philo[i].meal_mutex, NULL);
		pthread_mutex_init(&sim->philo[i].state_mutex, NULL);
		pthread_mutex_init(sim->philo[i].fork_l, NULL);
		pthread_mutex_init(sim->philo[i].fork_r, NULL);
		if (pthread_create(&sim->philo[i].thread, NULL, &philo_routine, &sim->philo[i]) != 0)
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

int8_t	join_philo_threads(t_simulation *sim)
{
	uint8_t	i;

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
