#include "libft.h"
#include <stdlib.h>

char	**ft_strremove_2d(char **src, int index)
{
	char	**new;
	int		n_of_arr;
	int		len;
	int		i;
	int		j;

	n_of_arr = 0;
	len = 0;
	i = 0;
	j = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 1);
	while (i < (n_of_arr - 1) && src[j])
	{
		if (j == index)
			j++;
		len = ft_strlen(src[j]) + 1;
		new[i] = malloc(sizeof(char) * len + 1);
		if (j > n_of_arr)
			ft_strlcpy(new[i], src[n_of_arr], len);
		else
			ft_strlcpy(new[i], src[j], len);
		i++;
		j++;
	}
	ft_free_2d(src);
	return (new);
}

