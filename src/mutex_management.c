#include "../includes/philo.h"
#include "../libft/libft.h"

static int8_t	init_philo_mutex_data(t_simulation *sim)
{
	uint8_t	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		if (pthread_mutex_init(&sim->philo[i].meal_mutex, NULL) != 0)
			return (error("Error: initializing philo mutexes failed.\n", -1));
		if (pthread_mutex_init(&sim->philo[i].state_mutex, NULL) != 0)
			return (error("Error: initializing philo mutexes failed.\n", -1));
		if (pthread_mutex_init(sim->philo[i].fork_l, NULL) != 0)
			return (error("Error: initializing philo mutexes failed.\n", -1));
		if (pthread_mutex_init(sim->philo[i].fork_r, NULL) != 0)
			return (error("Error: initializing philo mutexes failed.\n", -1));
		i++;
	}
	return (0);
}

static int8_t	destroy_philo_mutex_data(t_simulation *sim)
{
	uint8_t	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		pthread_mutex_destroy(&sim->philo[i].meal_mutex);
		pthread_mutex_destroy(&sim->philo[i].state_mutex);
		pthread_mutex_destroy(sim->philo[i].fork_l);
		pthread_mutex_destroy(sim->philo[i].fork_r);
		i++;
	}
	return (0);
}

int8_t	init_mutex_data(t_simulation *sim)
{
	if (init_philo_mutex_data(sim) == -1)
		return (-1);
	if (pthread_mutex_init(&sim->msg_mutex, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&sim->term_mutex, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&sim->start_sim_mutex, NULL) == -1)
		return (-1);
	return (0);
}

int8_t	destroy_mutex_data(t_simulation *sim)
{
	destroy_philo_mutex_data(sim);
	pthread_mutex_destroy(&sim->msg_mutex);
	pthread_mutex_destroy(&sim->term_mutex);
	pthread_mutex_destroy(&sim->start_sim_mutex);
	return (0);
}

