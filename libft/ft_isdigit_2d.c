/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_isdigit_2d.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 17:00:55 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/09 17:02:03 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_isdigit_2d(char *arr[])
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (arr[i])
	{
		while (arr[i][j])
		{
			if (ft_isdigit(arr[i][j]) == 0)
				return (ft_putstr_fd("Given arguments should contain \
numbers only.", STDERR_FILENO), -1);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}
