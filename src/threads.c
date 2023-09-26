#include "../includes/philo.h"
#include "../libft/libft.h"
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	*routine(void* arg)
{
	t_philo *philo = (t_philo*)arg;

	pthread_mutex_lock(&philo->start_mutex);
	philo->start_time = get_time();
	pthread_mutex_unlock(&philo->start_mutex);

	while (!simulation_should_stop(philo->sim))
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
	int	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		pthread_mutex_init(&sim->philo[i].start_mutex, NULL);
		pthread_mutex_init(&sim->philo[i].meal_mutex, NULL);
		pthread_mutex_init(sim->philo[i].fork_l, NULL);
		pthread_mutex_init(sim->philo[i].fork_r, NULL);
		if (pthread_create(&sim->philo[i].thread, NULL, &routine, &sim->philo[i]) != 0)
			return (ft_putstr_fd("Error creating thread!\n", STDERR_FILENO), -1);
		i++;
	}
	return (1);
}

int16_t	join_philo_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		if (pthread_join(sim->philo[i].thread, NULL) != 0)
			return (ft_putstr_fd("Error joining thread!\n", STDERR_FILENO), -1);
		pthread_mutex_destroy(&sim->philo[i].start_mutex);
		pthread_mutex_destroy(&sim->philo[i].meal_mutex);
		pthread_mutex_destroy(sim->philo[i].fork_l);
		pthread_mutex_destroy(sim->philo[i].fork_r);
		i++;
	}
	return (1);
}

static bool	is_philo_dead(t_philo *philo, int philo_id)
{
	int32_t	time_ellapsed;

	pthread_mutex_lock(&philo->meal_mutex);
	time_ellapsed = time_ellapsed_in_ms(philo->last_meal, get_time());
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_ellapsed >= (int32_t) philo->sim->time_to_die)
	{
		ft_printf("%d %d died\n", time_ellapsed_in_ms(philo->start_time, get_time()), philo_id);
		return (true);
	}
	return (false);
}

void	monitor_routine(t_simulation *sim)
{
	int i;

	i = 0;
	while (!sim->is_dead)
	{
		sim->is_dead = is_philo_dead(&sim->philo[i], i);
		if (sim->is_dead)
			return ;
		i++;
		if (i >= sim->number_of_philosophers)
			i = 0;
	}
}
