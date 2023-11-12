/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   thread_management.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:52:49 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/12 16:57:44 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>
#include <stdio.h>

static void	cleanup_program(t_simulation *sim, int n)
{
	sim->terminate = true;
	pthread_mutex_unlock(&sim->start_sim_mutex);
	clean_threads(sim, n);
	clean_simulation_data(sim);
}

int8_t	create_philo_threads(t_simulation *sim)
{
	uint8_t	i;

	i = 0;
	pthread_mutex_lock(&sim->start_sim_mutex);
	while (i < sim->number_of_philosophers)
	{
		if (pthread_create(&sim->philo[i].thread, NULL,
				&philo_routine, &sim->philo[i]) != 0)
			return (cleanup_program(sim, i), error("Error: thread creation failed!\n", -1));
		i++;
	}
	sim->start_time = get_time();
	i = 0;
	while (i < sim->number_of_philosophers)
	{
		sim->philo[i].last_meal = sim->start_time;
		i++;
	}
	pthread_mutex_unlock(&sim->start_sim_mutex);
	return (0);
}

int8_t	join_philo_threads(t_simulation *sim)
{
	uint8_t	i;
	int8_t	err;

	i = 0;
	err = 0;
	while (i < sim->number_of_philosophers)
	{
		// if (pthread_detach(sim->philo[i].thread) != 0)
		// {
		// 	ft_sleep(10);
		// 	// pthread_join(sim->philo[i].thread, NULL);
		// 	pthread_detach(sim->philo[i].thread);
		// 	error("Error: could not detach thread!\n", 0);
		// 	err = -1;
		// }
		if (pthread_join(sim->philo[i].thread, NULL) != 0)
		{
			ft_sleep(10);
			pthread_join(sim->philo[i].thread, NULL);
			error("Error: could not detach thread!\n", 0);
			err = -1;
		}
		i++;
	}
	destroy_mutex_data(sim);
	clean_simulation_data(sim);
	return (err);
}
