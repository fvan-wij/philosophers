/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils_time.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:54:12 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/12/01 11:16:21 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

int64_t	time_elapsed_in_ms(int64_t start_time, int64_t end_time)
{
	int64_t	delta_time;

	delta_time = end_time - start_time;
	return (delta_time);
}

int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int8_t	ft_sleep(int64_t ms)
{
	int8_t	err;
	int64_t	wake_up_time;

	err = 0;
	wake_up_time = get_time() + ms;
	while (err != -1)
	{
		if (get_time() >= wake_up_time)
			return (0);
		err = usleep(500);
	}
	return (err);
}

void	pray_before_meal(t_philo *philo)
{
	int64_t	time_to_die;
	int64_t	diff;
	float	multiplier;

	if (philo->sim->time_to_sleep >= philo->sim->time_to_eat)
		return ;
	pthread_mutex_lock(&philo->meal_mutex);
	time_to_die = time_elapsed_in_ms(philo->last_meal, get_time());
	pthread_mutex_unlock(&philo->meal_mutex);
	diff = time_to_die - philo->sim->time_to_eat;
	if (philo->sim->time_to_sleep < 90)
		multiplier = 2.5;
	else
		multiplier = 1.25;
	if (diff > 0)
		ft_sleep(diff * multiplier);
}
