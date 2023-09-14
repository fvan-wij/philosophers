#include "../includes/philo.h"
#include "../libft/libft.h"
#include <pthread.h>
#include <unistd.h>


void	*routine()
{
	ft_printf("Test from threads\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo		philo;
	pthread_t	t1;

	init_philosophers(argc, argv, &philo);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (ft_putstr_fd("Error creating thread!\n", STDERR_FILENO), 1);
	pthread_join(t1, NULL);

	return (0);
}
