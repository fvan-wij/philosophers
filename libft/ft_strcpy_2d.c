#include "libft.h"
#include <stdlib.h>

char	**ft_strcpy_2d(char **array)
{
	char	**copy;
	int		n_of_arr;
	int		len;
	int		i;

	n_of_arr = 0;
	len = 0;
	i = 0;
	while (array[n_of_arr])
		n_of_arr++;
	copy = ft_calloc(sizeof(char *), n_of_arr + 1);
	while (i < n_of_arr)
	{
		len = ft_strlen(array[i]) + 1;
		copy[i] = malloc(sizeof(char) * len + 1);
		ft_strlcpy(copy[i], array[i], len);
		i++;
	}
	return (copy);
}
