#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int ft_isarrnum(char *arr[])
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		while (arr[i][j])	
		{
			if (!ft_isalnum(arr[i][j]))
				return(ft_putstr_fd("Given arguments should contain numbers only.", STDERR_FILENO), -1);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	is_correct_argc(int argc)
{
	if (argc != 5 && argc != 6)
		return(ft_putstr_fd("This program takes at least 4 arguments or an optional 5th.", STDERR_FILENO), -1);
	return (1);
}

void	init_philosophers(int argc, char *argv[], t_philo *philo)
{
	if (!is_correct_argc(argc) && !ft_isarrnum(argv))
		exit(1);
	philo->number_of_philosophers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	ft_printf("number_of_philosophers: %s\ntime_to_die: %s\ntime_to_eat: %s\ntime_to_sleep: %s\n(optional)number_of_times_each_philosopher_must_eat: %s\n",
				argv[1], argv[2], argv[3], argv[4], argv[5]);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;

	init_philosophers(argc, argv, &philo);

	return (0);
}
