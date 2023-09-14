#include "libft.h"

char	**ft_strreplace_2d(char **src, char *str, int index)
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
	new = ft_calloc(sizeof(char *), n_of_arr + 1);
	while (i < n_of_arr)
	{
		if (i == index)
		{
			len = ft_strlen(str) + 1;
			new[i] = ft_calloc(sizeof(char), len + 1);
			ft_strlcpy(new[i], str, len);
		}
		else
		{
			len = ft_strlen(src[i]) + 1;
			new[i] = ft_calloc(sizeof(char), len + 1);
			ft_strlcpy(new[i], src[i], len);
		}
		i++;
	}
	ft_free_2d(src);
	return (new);
}
