#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>

int8_t	error(const char *msg, int8_t err)
{
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	return (err);
}
