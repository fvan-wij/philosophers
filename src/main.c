#include "../includes/philo.h"
#include "../libft/libft.h"
#include <pthread.h>
#include <unistd.h>

int pillen = 0;

void	*routine(void* arg)
{
	int i;

	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock((pthread_mutex_t*)arg);
		pillen++;
		i++;
		pthread_mutex_unlock((pthread_mutex_t*)arg);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo		philo;
	pthread_t	t1, t2;
	pthread_mutex_t	mutex;

	init_philosophers(argc, argv, &philo);
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, &mutex) != 0)
		return (ft_putstr_fd("Error creating thread!\n", STDERR_FILENO), 1);
	if (pthread_create(&t2, NULL, &routine, &mutex) != 0)
		return (ft_putstr_fd("Error creating thread!\n", STDERR_FILENO), 1);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);
	ft_printf("pillen: %d\n", pillen);

	return (0);
}
