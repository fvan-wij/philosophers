#ifndef PHILO_H 
# define PHILO_H 

# include <sys/time.h>
# include <pthread.h>

//###############################################################
//		DATA_STRUCTURES
//###############################################################

//				main struct
typedef struct 	s_philo {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				number_of_available_forks;
	pthread_mutex_t mutex;
}				t_philo;

//###############################################################
//		SOURCE FILES	
//###############################################################

//			main.c

//			time.c
long int	time_ellapsed_in_ms(suseconds_t init);

//			init.c
int 		ft_isdigit_2d(char *arr[]);
int			is_correct_argc(int argc);
void		init_philosophers(int argc, char *argv[], t_philo *philo);

#endif
