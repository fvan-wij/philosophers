#include "libft.h"

void	ft_putstr_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i++])
	{
		if (arr[i])
			ft_printf("%s\n", arr[i]);
	}
}
