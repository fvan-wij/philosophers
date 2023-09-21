#ifndef PHILO_H 
# define PHILO_H 

# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>
# include <stdbool.h>

//###############################################################
//		DATA_STRUCTURES
//###############################################################

//				philosopher state enumerator
typedef enum e_state {
	IS_EATING,
	IS_SLEEPING,
	IS_PONDERING,
	IS_DEAD,
	UNITIALIZED,
}	t_state;

typedef pthread_mutex_t t_fork;

typedef enum e_fork_index {
	LEFT,
	RIGHT,
} 	t_fork_index;

//				philo struct -> contains data about the state of each seperate philosopher;
typedef struct s_philo {
	pthread_t			thread;	
	pthread_mutex_t		start_mutex;
	t_fork				fork[2];
	size_t				start_time;
	int					state;
	int					philo_id;
	struct s_simulation	*sim;
}				t_philo;


//				main struct -> contains data about the rules of the simulation;
typedef struct 	s_simulation {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				number_of_available_forks;
	int				is_dead;
	pthread_mutex_t state_mutex;
	t_philo			*philo;
	pthread_t		monitor;
	t_fork			*forks;
}				t_simulation;

//###############################################################
//		SOURCE FILES	
//###############################################################

//			main.c

//			time.c
long int	time_ellapsed_in_ms(size_t init);
size_t		start_timer();

//			init.c
void		init_simulation_data(int argc, char *argv[], t_simulation *sim);

//			threads.c
int			create_philo_threads(t_simulation *sim);
int			join_philo_threads(t_simulation *sim);
int 		monitor_routine(t_simulation *sim);


#endif
