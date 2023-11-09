#include "../includes/philo.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	free_arr(void *arr, uint8_t n)
{
	uint8_t	i;

	i = 0;
	while (i < n)
	{
		free(&arr[i]);
		i++;
	}
}
