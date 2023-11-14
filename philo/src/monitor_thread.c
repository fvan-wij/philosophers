/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   monitor_thread.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:48:04 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/14 18:43:16 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static	void	terminate_simulation(t_simulation *sim)
{
	pthread_mutex_lock(&sim->term_mutex);
	sim->terminate = true;
	pthread_mutex_unlock(&sim->term_mutex);
}

static bool	philo_is_dead(t_philo *philo)
{
	int64_t	time_ellapsed;
	int64_t	time;

	time_ellapsed = 0;
	time = 0;
	time = get_time();
	bool isdead = false;
	pthread_mutex_lock(&philo->meal_mutex);
	time_ellapsed = time_ellapsed_in_ms(philo->last_meal, time);
	if (time_ellapsed >= philo->sim->time_to_die)
		isdead = true;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (isdead)
	{
		terminate_simulation(philo->sim);
		ft_sleep(4);
		printf("%ld %d died\n", time_ellapsed_in_ms(philo->sim->start_time, time), philo->id);
		// print_action(philo, "%ld %d died\n");
		return (true);
	}
	return (false);
}

static bool	philo_is_full(t_philo *philo)
{
	bool	temp;

	pthread_mutex_lock(&philo->state_mutex);
	temp = philo->is_full;
	pthread_mutex_unlock(&philo->state_mutex);
	return (temp);
}

void	monitor_routine(t_simulation *sim)
{
	uint8_t	i;
	uint8_t	count;

	i = 0;
	count = 0;
	while (1)
	{
		if (philo_is_dead(&sim->philo[i]))
			return ;
		count += philo_is_full(&sim->philo[i]);
		i++;
		if (count == sim->number_of_philosophers)
			return (terminate_simulation(sim));
		else if (i >= sim->number_of_philosophers)
		{
			i = 0;
			count = 0;
			// ft_sleep(250);
			ft_sleep(1);
		}
	}
}
