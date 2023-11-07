#ifndef PHILO_H 
# define PHILO_H 

# include <pthread.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>

# define MS(ms) ((ms) * (1000))

//###############################################################
//		DATA_STRUCTURES
//###############################################################

typedef pthread_mutex_t t_fork;

//				philo struct -> contains data about the state of each seperate philosopher;
typedef struct s_philo {
	pthread_t			thread;	
	int32_t				state;
	int32_t				philo_id;
	int32_t				meal_count;
	int64_t				last_meal;
	t_fork				*fork_l;
	t_fork				*fork_r;
	bool				is_full;
	int8_t				(*eat_func)(struct s_philo *);
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		state_mutex;
	struct s_simulation	*sim;
}				t_philo;

//				main struct -> contains data about the rules of the simulation;
typedef struct 	s_simulation {
	pthread_t			monitor;
	t_philo				*philo;
	int64_t				start_time;
	int32_t				number_of_philosophers;
	int32_t				time_to_die;
	int32_t				time_to_eat;
	int32_t				time_to_sleep;
	int32_t				number_of_times_each_philosopher_must_eat;
	int32_t				number_of_available_forks;
	t_fork				*forks;
	bool				terminate;
	pthread_mutex_t		start_time_mutex;
	pthread_mutex_t 	term_mutex;
	pthread_mutex_t 	start_sim_mutex;
	pthread_mutex_t		msg_mutex;
}				t_simulation;

//###############################################################
//		SOURCE FILES	
//###############################################################

//			main.c

//			time.c
int64_t		time_elapsed_in_ms(int64_t start_time, int64_t end_time);
int64_t		get_time();
int8_t		ft_usleep(int64_t useconds);

//			init.c
void		init_simulation_data(int argc, char *argv[], t_simulation *sim);

//			threads.c
int16_t		create_philo_threads(t_simulation *sim);
int16_t		join_philo_threads(t_simulation *sim);
int8_t		print_action(t_philo *philo, const char *msg);

//			monitor.c
void		monitor_routine(t_simulation *sim);

//			actions.c
int8_t		philo_eat(t_philo *philo);
int8_t		philo_sleep(t_philo *philo);
int8_t		philo_think(t_philo *philo);
int8_t		plural_eat_routine(t_philo *philo);
int8_t		plural_eat_routine_odd(t_philo *philo);
int8_t		plural_eat_routine_even(t_philo *philo);
int8_t		singular_eat_routine(t_philo *philo);


#endif
