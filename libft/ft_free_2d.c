/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_free_2d.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/30 15:43:21 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/09/14 21:06:12 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}