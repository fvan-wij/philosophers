/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_getenv.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 17:00:30 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/09 17:00:47 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	var_exists(char	**env, char *var)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var);
	if (var_len <= 0)
		return (-1);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_getenv(char *var_name, char **env)
{
	char	*value;
	int		var_index;

	var_index = var_exists(env, var_name);
	if (var_index == -1)
		return (NULL);
	else
		value = ft_strdup(ft_strchr(env[var_index], '=') + 1);
	return (value);
}
