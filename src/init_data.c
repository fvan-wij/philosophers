/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_data.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 15:24:36 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/09 15:41:53 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../libft/libft.h"
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
	sim->number_of_philosophers = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->terminate = false;
	if (argv[5])
		sim->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		sim->number_of_times_each_philosopher_must_eat = 0;
	if (sim->number_of_philosophers > 200
		|| sim->time_to_die > 2147483647
		|| sim->time_to_eat > 2147483647
		|| sim->time_to_sleep > 2147483647
		|| sim->number_of_times_each_philosopher_must_eat > 2147483647)
		return (ft_putstr_fd("Error: input has exceeded the maximum integer\
size (2,147,483,647).\n", STDERR_FILENO), -1);
	if (sim->number_of_philosophers >= 1 && sim->time_to_die >= 1
		&& sim->time_to_eat >= 1 && sim->time_to_sleep >= 1)
		return (1);
	else
		return (error("Error: n_of_philosophers, time_to_die, time_to_eat and\
time_to_sleep should have at least a value of 1.\n", -1));
}

static void	init_philosopher_states(t_simulation *sim)
{
	int16_t	i;

	i = 0;
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
}

static int8_t	allocate_data(t_simulation *sim)
{
	sim->philo = ft_calloc(sim->number_of_philosophers, sizeof(t_philo));
	if (!sim->philo)
	{
		free(sim->philo);
		return (error("Error: philo struct allocation failed.\n", -1));
	}
	sim->forks = ft_calloc(sim->number_of_philosophers, sizeof(t_fork));
	if (!sim->forks)
	{
		free(sim->forks);
		free(sim->philo);
		return (error("Error: fork allocation failed.\n", -1));
	}
	if (init_mutex_data(sim) == -1)
	{
		free(sim->philo);
		free(sim->forks);
		return (error("Error: initializing mutex data failed.\n", -1));
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
	init_philosopher_states(sim);
	return (0);
}
