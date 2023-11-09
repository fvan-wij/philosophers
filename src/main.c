/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:47:52 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/09 16:47:53 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_simulation	sim;

	if (init_simulation_data(argc, argv, &sim) == -1)
		return (1);
	if (create_philo_threads(&sim) == -1)
		return (1);
	monitor_routine(&sim);
	if (join_philo_threads(&sim) == -1)
		return (1);
	destroy_mutex_data(&sim);
	clean_simulation_data(&sim);
	return (0);
}
