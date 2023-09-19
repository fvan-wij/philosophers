#include "../includes/philo.h"
#include "../libft/libft.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

void	*routine(void* arg)
{
	size_t	time_ellapsed;

	t_philo *philo = (t_philo*)arg;
	pthread_mutex_lock(&philo->sim->mutex);
	printf("Philo #%d has started living\n", philo->philo_id);
	philo->start_time = start_timer();
	philo->state = IS_PONDERING;
	while (philo->state != IS_DEAD)
	{
		// if (philo->state == IS_PONDERING)
		// 	ft_printf("Philo %d is thinking...\n", philo->philo_id);
		time_ellapsed = time_ellapsed_in_ms(philo->start_time);
		if (time_ellapsed >= (size_t) philo->sim->time_to_die)
		{
			ft_printf("%d %d has died.\n", time_ellapsed, philo->philo_id);
			philo->state = IS_DEAD;
		}
	}
	pthread_mutex_unlock(&philo->sim->mutex);
	return NULL;
}

int	create_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		pthread_create(&sim->philo[i].thread, NULL, &routine, &sim->philo[i]) != 0)
			return (ft_putstr_fd("Error creating thread!\n", STDERR_FILENO), -1);
		i++;
	}
	return (1);
}

int	join_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		if (pthread_join(sim->philo[i].thread, NULL) != 0)
			return (ft_putstr_fd("Error joining thread!\n", STDERR_FILENO), -1);
		i++;
	}
	return (1);
}
