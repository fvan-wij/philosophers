/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_data.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 15:24:36 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/12 17:43:51 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	is_correct_argc(int argc)
{
	if (argc != 5 && argc != 6)
		return (error("Error: this program takes at least \
4 arguments or an optional 5th.", -1));
	return (1);
}

static int	validate_input(char *argv[], t_simulation *sim)
{
	if (set_sim_rules(sim, argv) == -1)
		return (-1);
	if (sim->number_of_philosophers >= 1 && sim->time_to_die >= 1
		&& sim->time_to_eat >= 1 && sim->time_to_sleep >= 1)
		return (1);
	else
		return (error("Error: arguments should have a value of at least 1.\n", -1));
}

static void	init_philosopher_states(t_simulation *sim, uint8_t i)
{
	while (i < sim->number_of_philosophers)
	{
		sim->philo[i].sim = sim;
		sim->philo[i].id = i + 1;
		sim->philo[i].meal_count = 0;
		sim->philo[i].last_meal = 0;
		sim->philo[i].fork_l = &sim->forks[i + 1];
		sim->philo[i].fork_r = &sim->forks[i];
		sim->philo[i].is_full = false;
		if (i == (sim->number_of_philosophers - 1))
		{
			sim->philo[i].fork_l = &sim->forks[0];
			sim->philo[i].fork_r = &sim->forks[i];
		}
		i++;
	}
	if (sim->time_to_eat >= sim->time_to_die)
		sim->time_to_eat = sim->time_to_die;
	if (sim->time_to_sleep >= sim->time_to_die)
		sim->time_to_sleep = sim->time_to_die;
	if (sim->time_to_eat < 5)
		sim->delay =5;
	else
		sim->delay = sim->time_to_eat / 2;
}

static int8_t	allocate_data(t_simulation *sim)
{
	sim->philo = malloc(sim->number_of_philosophers * sizeof(t_philo));
	if (!sim->philo)
	{
		free(sim->philo);
		return (error("Error: philo struct allocation failed.\n", -1));
	}
	sim->forks = malloc(sim->number_of_philosophers * sizeof(t_fork));
	if (!sim->forks)
	{
		clean_simulation_data(sim);
		return (error("Error: fork allocation failed.\n", -1));
	}
	return (0);
}

int8_t	init_simulation_data(int argc, char *argv[], t_simulation *sim)
{
	if (is_correct_argc(argc) == -1 || ft_isdigit_2d(argv) == -1)
		return (-1);
	if (validate_input(argv, sim) == -1)
		return (-1);
	if (allocate_data(sim) == -1)
		return (-1);
	init_philosopher_states(sim, 0);
	if (init_mutex_data(sim) == -1)
		return (clean_simulation_data(sim), -1);
	return (0);
}
