#include "../includes/philo.h"
#include "../libft/libft.h"

int8_t	init_mutex_data(t_simulation *sim)
{
	pthread_mutex_init(&sim->msg_mutex, NULL);
	pthread_mutex_init(&sim->term_mutex, NULL);
	pthread_mutex_init(&sim->start_sim_mutex, NULL);
	return (0);
}

int8_t	destroy_mutex_data(t_simulation *sim)
{
	pthread_mutex_destroy(&sim->msg_mutex);
	pthread_mutex_destroy(&sim->term_mutex);
	pthread_mutex_destroy(&sim->start_sim_mutex);
	return (0);
}

