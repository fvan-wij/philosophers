#ifndef PHILO_H 
# define PHILO_H 

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

//###############################################################
//		DATA_STRUCTURES
//###############################################################

//				philo struct -> contains data about the state of each seperate philosopher;
typedef struct s_philo {
	pthread_t	thread;	
	bool		is_eating;	
	bool		is_sleeping;
	bool		is_pondering;
}				t_philo;

//				main struct -> contains data about the rules of the simulation;
typedef struct 	s_simulation {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				number_of_available_forks;
	pthread_mutex_t mutex;
	t_philo			*philo;
}				t_simulation;


//###############################################################
//		SOURCE FILES	
//###############################################################

//			main.c

//			time.c
long int	time_ellapsed_in_ms(suseconds_t init);

//			init.c
void		init_simulation_data(int argc, char *argv[], t_simulation *sim);

//			threads.c
int			create_threads(t_simulation *sim);
int			join_threads(t_simulation *sim);


#endif
