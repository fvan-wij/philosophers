#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	is_correct_argc(int argc)
{
	if (argc != 5 && argc != 6)
		return(ft_putstr_fd("This program takes at least 4 arguments or an optional 5th.", STDERR_FILENO), -1);
	return (1);
}

static int	validate_input(t_simulation *sim)
{
	if (sim->number_of_philosophers >= 1 && sim->time_to_die >= 1 && sim->time_to_eat >= 1 && sim->time_to_sleep >= 1)
		return (1);
	else
		return(ft_putstr_fd("Arguments should have at least a value of 1.\n", STDERR_FILENO), -1);
}

static void	init_philosopher_states(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		sim->philo[i].sim = sim;
		sim->philo[i].philo_id = i;
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
}

void	init_simulation_data(int argc, char *argv[], t_simulation *sim)
{
	if (is_correct_argc(argc) == -1 || ft_isdigit_2d(argv) == -1)
		exit(1);
	sim->number_of_philosophers = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->terminate = false;
	if (argv[5])
		sim->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (validate_input(sim) == -1)
		exit(1);
	sim->philo = ft_calloc(sim->number_of_philosophers, sizeof(t_philo));
	sim->forks = ft_calloc(sim->number_of_philosophers, sizeof(t_fork));
	ft_printf("number_of_philosophers: %d, time_to_die: %d, time_to_eat: %d, time_to_sleep: %d, number_of_times_each_philosopher_must_eat: %d\n", sim->number_of_philosophers, sim->time_to_die, sim->time_to_eat, sim->time_to_sleep, sim->number_of_times_each_philosopher_must_eat);
	init_philosopher_states(sim);
}

