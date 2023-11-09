#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_simulation	sim;

	if (init_simulation_data(argc, argv, &sim) == -1)
		return (1);

	// Create Philo trheads
	create_philo_threads(&sim);
	// Monitor simulaiton
	monitor_routine(&sim);

	// Join philo threads
	join_philo_threads(&sim);
	// Destroy mutexes
	destroy_mutex_data(&sim);
	return (0);
}
