/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo_threads.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:49:34 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/10 15:43:40 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../libft/libft.h"
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int8_t	philo_eat(t_philo *philo)
{
	return (philo->eat_func(philo));
}

static int8_t	philo_sleep(t_philo *philo)
{
	if (print_action(philo, "is sleeping\n") == -1)
		return (-1);
	ft_sleep(philo->sim->time_to_sleep);
	return (1);
}

static int8_t	philo_think(t_philo *philo)
{
	if (print_action(philo, "is thinking\n") == -1)
		return (-1);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->sim->number_of_philosophers == 1)
		philo->eat_func = &singular_eat_routine;
	else
		philo->eat_func = &plural_eat_routine;
	pthread_mutex_lock(&philo->sim->start_sim_mutex);
	pthread_mutex_unlock(&philo->sim->start_sim_mutex);
	if (philo->sim->terminate)
		return (NULL);
	if (philo->id % 2 != 0)
		ft_sleep((philo->sim->time_to_eat) / 2);
	while (1)
	{
		if (philo_eat(philo) == -1)
			break ;
		if (philo_sleep(philo) == -1)
			break ;
		if (philo_think(philo) == -1)
			break ;
	}
	return (NULL);
}
