#include "../includes/philo.h"
#include "../libft/libft.h"
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

bool	simulation_should_stop(t_simulation *sim, t_fork *left, t_fork *right)
{
	bool temp_state;

	temp_state = sim->terminate;
	if (temp_state && left)
		pthread_mutex_unlock(left);
	if (temp_state && right)
		pthread_mutex_unlock(right);
	return (temp_state);
}

static void	*routine(void* arg)
{
	t_philo *philo = (t_philo*)arg;

	while (1)
	{
		if (simulation_should_stop(philo->sim, NULL, NULL) || philo_eat(philo) == -1)
			break ;
		if (simulation_should_stop(philo->sim, NULL, NULL) || philo_sleep(philo) == -1)
			break ;
		philo_think(philo);
	}
	return NULL;
}

int16_t	create_philo_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->start_mutex);
	sim->start_time = get_time();
	pthread_mutex_unlock(&sim->start_mutex);
	while (i < sim->number_of_philosophers)
	{
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
		ft_printf("%d %d died\n", time_ellapsed_in_ms(philo->sim->start_time, get_time()), philo_id);
		return (true);
	}
	return (false);
}

static bool	is_philo_full(t_philo *philo, int32_t number_of_times_each_philosopher_must_eat)
{
	if (philo->meal_count >= number_of_times_each_philosopher_must_eat)
	{
		printf("--> philo %d finished eating\n", philo->philo_id + 1);
		return (true);
	}
	return (false);
}

void	monitor_routine(t_simulation *sim)
{
	int16_t i;

	i = 0;
	while (1)
	{
		if (is_philo_dead(&sim->philo[i], i))
			break ;
		if (sim->number_of_times_each_philosopher_must_eat >= 1 && is_philo_full(&sim->philo[i], sim->number_of_times_each_philosopher_must_eat))
			break ;
		i++;
		if (i >= sim->number_of_philosophers)
			i = 0;
	}
	pthread_mutex_lock(&sim->state_mutex);
	sim->terminate = true;
	pthread_mutex_unlock(&sim->state_mutex);
}
