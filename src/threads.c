#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>

void	*routine(void* arg)
{
	int	i;
	static int test;
	t_simulation *sim = (t_simulation*)arg;

	pthread_mutex_lock(&sim->mutex);
	i = 0;
	while (i < 1000000)
	{
		test++;
		i++;
	}
	pthread_mutex_unlock(&sim->mutex);
	ft_printf("test = %d\n", test);
	return NULL;
}

int	create_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		if (pthread_create(&sim->philo[i].thread, NULL, &routine, &sim->mutex) != 0)
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
