#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_simulation	sim;

	//Pre-mortem
	init_simulation_data(argc, argv, &sim);
	pthread_mutex_init(&sim.start_mutex, NULL);
	pthread_mutex_init(&sim.msg_mutex, NULL);
	pthread_mutex_init(&sim.state_mutex, NULL);
	pthread_mutex_init(&sim.start_sim_mutex, NULL);
	create_philo_threads(&sim);
	monitor_routine(&sim);

	//Post-mortem
	join_philo_threads(&sim);
	pthread_mutex_destroy(&sim.start_mutex);
	pthread_mutex_destroy(&sim.state_mutex);
	pthread_mutex_destroy(&sim.start_sim_mutex);
	pthread_mutex_destroy(&sim.msg_mutex);
	return (0);
}
