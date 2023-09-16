#include "../includes/philo.h"
#include "../libft/libft.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef struct s_test {
	pthread_mutex_t mutex;
	int*	result;
} t_test;

void	*routine(void* arg)
{
	t_test *test = (t_test*)arg;
	int	value;

	pthread_mutex_lock(&test->mutex);
	value = (rand() % 6) + 1;
	*test->result = value;
	pthread_mutex_unlock(&test->mutex);
	return NULL;
}

int	main(int argc, char *argv[])
{
	t_philo		philo;
	t_test test;

	struct timeval tv;
	suseconds_t init;

	gettimeofday(&tv, NULL);
	init = tv.tv_usec;
	test.result = malloc(sizeof(int));
	init_philosophers(argc, argv, &philo);
	srand(time(NULL));
	pthread_t	thread[philo.number_of_philosophers];
	pthread_mutex_init(&test.mutex, NULL);
	int i = 0;
	while (i < philo.number_of_philosophers)
	{
		if (pthread_create(&thread[i], NULL, &routine, &test.mutex) != 0)
			return (ft_putstr_fd("Error creating thread!\n", STDERR_FILENO), 1);
		i++;
	}
	i = 0;
	while (i < philo.number_of_philosophers)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (ft_putstr_fd("Error joining thread!\n", STDERR_FILENO), 2);
		ft_printf("Thread[%d] result: %d\n", i, *test.result);
		i++;
	}
	pthread_mutex_destroy(&test.mutex);
	free(test.result);
	// usleep(10000);
	time_ellapsed_in_ms(init);
	return (0);
}
