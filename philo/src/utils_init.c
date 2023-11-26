/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils_init.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: flip <marvin@42.fr>                         +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/12 13:53:06 by flip          #+#    #+#                 */
/*   Updated: 2023/11/26 15:26:19 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#define ERR_INPUT "Error: simulation only accepts input \
between 1 and INT_MAX.\n"
#define ERR_MAXPH "Error: maximum number of philosophers \
(200) exceeded.\n"

static int32_t	skip_whitespace(int32_t i, char *int_str)
{
	while (int_str[i] == ' ' || int_str[i] == '\t'
		|| int_str[i] == '\r' || int_str[i] == '\n'
		|| int_str[i] == '\v' || int_str[i] == '\f')
		i++;
	return (i);
}

static int32_t	convert_atoi(char *int_str, int32_t i, int8_t *err)
{
	int64_t	ret;

	ret = 0;
	while ((int_str[i] >= 48 && int_str[i] <= 57) && int_str[i] != '\0')
	{
		ret = ret * 10 + (int_str[i] - '0');
		if (ret > INT_MAX || ret < INT_MIN)
			return (*err = -1, -1);
		i++;
	}
	return (ret);
}

static int8_t	set_val(int32_t	*val, char *str)
{
	int8_t	err;

	err = 0;
	*val = ft_atoi_overflow(str, &err);
	if (err == -1)
		error("Error: atoi overflow.\n", -1);
	return (0);
}

int32_t	ft_atoi_overflow(const char *str, int8_t *err)
{
	int64_t		ret;
	char		*int_str;
	int			i;
	int			neg_check;

	int_str = (char *) str;
	ret = 0;
	i = 0;
	neg_check = 1;
	*err = 0;
	i = skip_whitespace(i, int_str);
	if (int_str[i] == '-')
		neg_check = -neg_check;
	while (int_str[i] == '-' || int_str[i] == '+')
	{
		i++;
		if (i > 1)
			return (0);
	}
	ret = convert_atoi(int_str, i, err);
	return (ret * neg_check);
}

int8_t	set_sim_rules(t_simulation *sim, char *argv[])
{
	if (set_val(&sim->number_of_philosophers, argv[1]) == -1)
		return (error(ERR_INPUT, -1));
	if (set_val(&sim->time_to_die, argv[2]) == -1)
		return (error(ERR_INPUT, -1));
	if (set_val(&sim->time_to_eat, argv[3]) == -1)
		return (error(ERR_INPUT, -1));
	if (set_val(&sim->time_to_sleep, argv[4]) == -1)
		return (error(ERR_INPUT, -1));
	if (argv[5])
	{
		if (set_val(&sim->number_of_times_each_philosopher_must_eat,
				argv[5]) == -1)
			return (error(ERR_INPUT, -1));
	}
	else
		sim->number_of_times_each_philosopher_must_eat = 0;
	if (sim->number_of_philosophers > 200)
		return (error(ERR_MAXPH, -1));
	sim->terminate = false;
	return (0);
}
