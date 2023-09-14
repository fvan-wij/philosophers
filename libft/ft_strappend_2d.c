#include "libft.h"
#include <stdlib.h>

char	**ft_strappend_2d(char **src, char *str)
{
	char	**new;
	int		n_of_arr;
	int		len;
	int		i;

	n_of_arr = 0;
	len = 0;
	i = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 2);
	while (i < n_of_arr)
	{
		len = ft_strlen(src[i]) + 1;
		new[i] = malloc(sizeof(char) * len + 1);
		ft_strlcpy(new[i], src[i], len);
		i++;
	}
	len = ft_strlen(str) + 1;
	new[i] = malloc(sizeof(char) * len + 1);
	ft_strlcpy(new[i], str, len);
	ft_free_2d(src);
	return (new);
}
