/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   eat_routines.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:46:22 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/12 14:05:09 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void	update_last_meal_time(t_philo *philo)
{
	int64_t	time;

	time = get_time();
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->meal_mutex);
}

static void	update_meal_count(t_philo *philo)
{
	if (philo->sim->number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->meal_mutex);
	}
}

static void	poll_if_full(t_philo *philo)
{
	if (philo->sim->number_of_times_each_philosopher_must_eat > 0
		&& philo->meal_count
		>= philo->sim->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->state_mutex);
		philo->is_full = true;
		pthread_mutex_unlock(&philo->state_mutex);
	}
}

int8_t	plural_eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_r);
	print_action(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->fork_l);
	print_action(philo, "has taken a fork\n");
	print_action(philo, "is eating\n");
	update_last_meal_time(philo);
	ft_sleep(philo->sim->time_to_eat);
	update_meal_count(philo);
	poll_if_full(philo);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	return (1);
}

int8_t	singular_eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_r);
	print_action(philo, "has taken a fork\n");
	pthread_mutex_unlock(philo->fork_r);
	return (1);
}
