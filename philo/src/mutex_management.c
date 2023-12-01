/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   mutex_management.c                                :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:49:17 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/12/01 11:16:44 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	destroy_on_failure(t_simulation *sim, int16_t meal_count,
								int16_t state_count, int16_t fork_count)
{
	while (meal_count-- > 0)
		pthread_mutex_destroy(&sim->philo[meal_count].meal_mutex);
	while (state_count-- > 0)
		pthread_mutex_destroy(&sim->philo[state_count].meal_mutex);
	while (fork_count-- > 0)
		pthread_mutex_destroy(&sim->forks[fork_count]);
}

static int8_t	init_philo_mutex_data(t_simulation *sim)
{
	uint8_t	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		if (pthread_mutex_init(&sim->philo[i].meal_mutex, NULL) != 0)
			return (destroy_on_failure(sim, i, 0, 0), -1);
		if (pthread_mutex_init(&sim->philo[i].state_mutex, NULL) != 0)
			return (destroy_on_failure(sim, i + 1, i, 0), -1);
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (destroy_on_failure(sim, i + 1, i + 1, i), -1);
		i++;
	}
	return (0);
}

static int8_t	destroy_philo_mutex_data(t_simulation *sim)
{
	uint8_t	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		pthread_mutex_destroy(&sim->philo[i].meal_mutex);
		pthread_mutex_destroy(&sim->philo[i].state_mutex);
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	return (0);
}

int8_t	init_mutex_data(t_simulation *sim)
{
	if (init_philo_mutex_data(sim) == -1)
		return (-1);
	if (pthread_mutex_init(&sim->msg_mutex, NULL) == -1)
		return (destroy_philo_mutex_data(sim), -1);
	if (pthread_mutex_init(&sim->term_mutex, NULL) == -1)
	{
		destroy_philo_mutex_data(sim);
		return (pthread_mutex_destroy(&sim->msg_mutex), -1);
	}
	if (pthread_mutex_init(&sim->start_sim_mutex, NULL) == -1)
	{
		destroy_philo_mutex_data(sim);
		pthread_mutex_destroy(&sim->msg_mutex);
		return (pthread_mutex_destroy(&sim->term_mutex), -1);
	}
	return (0);
}

int8_t	destroy_mutex_data(t_simulation *sim)
{
	destroy_philo_mutex_data(sim);
	pthread_mutex_destroy(&sim->msg_mutex);
	pthread_mutex_destroy(&sim->term_mutex);
	pthread_mutex_destroy(&sim->start_sim_mutex);
	return (0);
}
