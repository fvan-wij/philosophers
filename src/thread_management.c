/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   thread_management.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:52:49 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/09 16:53:39 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>

int8_t	create_philo_threads(t_simulation *sim)
{
	uint8_t	i;

	i = 0;
	pthread_mutex_lock(&sim->start_sim_mutex);
	while (i < sim->number_of_philosophers)
	{
		if (pthread_create(&sim->philo[i].thread, NULL,
				&philo_routine, &sim->philo[i]) != 0)
			return (clean_simulation_data(sim),
				error("Error: thread creation failed!\n", -1));
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

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		if (pthread_join(sim->philo[i].thread, NULL) != 0)
		{
			clean_simulation_data(sim);
			return (ft_putstr_fd("Error: could not join thread!\n",
					STDERR_FILENO), -1);
		}
		i++;
	}
	return (1);
}
