/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils_misc.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:53:58 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/14 13:48:50 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

int8_t	print_action(t_philo *philo, const char *msg)
{
	bool	temp;
	int64_t	time;
	int64_t	elapsed_time;

	pthread_mutex_lock(&philo->sim->term_mutex);
	temp = philo->sim->terminate;
	pthread_mutex_unlock(&philo->sim->term_mutex);
	if (temp)
		return (-1);
	else
	{
		pthread_mutex_lock(&philo->sim->msg_mutex);
		time = get_time();
		elapsed_time = time_ellapsed_in_ms(philo->sim->start_time, time);
		printf("%ld %d %s", elapsed_time, philo->id, msg);
		pthread_mutex_unlock(&philo->sim->msg_mutex);
		return (1);
	}
}

void	clean_simulation_data(t_simulation *sim)
{
	free(sim->philo);
	free(sim->forks);
}

void	clean_threads(t_simulation *sim, int16_t n)
{
	uint8_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_join(sim->philo[i].thread, NULL) != 0)
			error("Error: thread joining failed.\n", -1);
		i++;
	}
}

int8_t	error(const char *msg, int8_t err)
{
	if (msg)
		printf("%s", msg);
	return (err);
}

int8_t	ft_isdigit_2d(char *arr[])
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (arr[i])
	{
		while (arr[i][j])
		{
			if (arr[i][j] >= '0' && arr[i][j] <= '9')
				j++;
			else
				return (error("Error: given arguments should contain \
positive integers only.\n", -1));
		}
		j = 0;
		i++;
	}
	return (1);
}
