/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils_misc.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:53:58 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/09 16:53:59 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../libft/libft.h"
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

int8_t	error(const char *msg, int8_t err)
{
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	return (err);
}
