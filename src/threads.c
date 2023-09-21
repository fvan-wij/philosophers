#include "../includes/philo.h"
#include "../libft/libft.h"
#include <pthread.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	check_state(t_simulation *sim)
{
	int temp_state;

	pthread_mutex_lock(&sim->state_mutex);
	temp_state = sim->is_dead;
	pthread_mutex_unlock(&sim->state_mutex);
	return (temp_state);
}

void	*routine(void* arg)
{
	t_philo *philo = (t_philo*)arg;

	pthread_mutex_lock(&philo->start_mutex);
	philo->start_time = start_timer();
	pthread_mutex_unlock(&philo->start_mutex);
	printf("Philo #%d has started living\n", philo->philo_id);
	while (check_state(philo->sim) != 1)
	{
		pthread_mutex_lock(&philo->fork[LEFT]);
		pthread_mutex_lock(&philo->fork[RIGHT]);
		printf("%ld %d is eating.", time_ellapsed_in_ms(philo->start_time), philo->philo_id);
		usleep(philo->sim->time_to_sleep * 1000);
		pthread_mutex_unlock(&philo->fork[LEFT]);
		pthread_mutex_unlock(&philo->fork[RIGHT]);
		// Try to eat & sleep afterwards
		// else, think
	}
	usleep(10000);
	return NULL;
}

int	create_philo_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		pthread_mutex_init(&sim->philo[i].start_mutex, NULL);
		pthread_mutex_init(&sim->philo[i].fork[LEFT], NULL);
		pthread_mutex_init(&sim->philo[i].fork[RIGHT], NULL);
		if (pthread_create(&sim->philo[i].thread, NULL, &routine, &sim->philo[i]) != 0)
			return (ft_putstr_fd("Error creating thread!\n", STDERR_FILENO), -1);
		i++;
	}
	return (1);
}

int	join_philo_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		pthread_mutex_destroy(&sim->philo[i].start_mutex);
		pthread_mutex_destroy(&sim->philo[i].fork[LEFT]);
		pthread_mutex_destroy(&sim->philo[i].fork[RIGHT]);
		if (pthread_join(sim->philo[i].thread, NULL) != 0)
			return (ft_putstr_fd("Error joining thread!\n", STDERR_FILENO), -1);
		i++;
	}
	return (1);
}

int	is_philo_dead(t_philo *philo, int philo_id)
{
	size_t	time_ellapsed;

	pthread_mutex_lock(&philo->start_mutex);
	time_ellapsed = time_ellapsed_in_ms(philo->start_time);
	pthread_mutex_unlock(&philo->start_mutex);
	if (time_ellapsed >= (size_t) philo->sim->time_to_die)
	{
		ft_printf("%d %d has died.\n", time_ellapsed, philo_id);
		return (1);
	}
	return (0);
}

int monitor_routine(t_simulation *sim)
{
	int i;

	i = 0;
	while (sim->is_dead != 1)
	{
		if (is_philo_dead(&sim->philo[i], i))
		{
			sim->is_dead = 1;
			exit(1);
		}
		i++;
		if (i >= sim->number_of_philosophers)
			i = 0;
	}
	return (0);
}
