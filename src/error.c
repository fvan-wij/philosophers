#include "../includes/philo.h"
#include "../libft/libft.h"
#include <unistd.h>

int8_t	error_log(const char *msg, t_error err)
{
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	return (err);
}
