#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_simulation	sim;

	init_simulation_data(argc, argv, &sim);
	pthread_mutex_init(&sim.mutex, NULL);
	create_threads(&sim);
	join_threads(&sim);
	pthread_mutex_destroy(&sim.mutex);
	return (0);
}
