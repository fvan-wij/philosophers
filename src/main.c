#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_simulation	sim;
	// t_philo			philo[ft_atoi(argv[1])];
	// 
	// sim.philo = philo;
	init_simulation_data(argc, argv, &sim);
	pthread_mutex_init(&sim.state_mutex, NULL);
	create_philo_threads(&sim);
	monitor_routine(&sim);
	join_philo_threads(&sim);
	pthread_mutex_destroy(&sim.state_mutex);
	return (0);
}
