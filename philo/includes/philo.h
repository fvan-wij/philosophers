/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 16:57:52 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/14 14:14:42 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H 
# define PHILO_H 

# include <pthread.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>

//############################################################### 
//			DATA_STRUCTURES
//###############################################################

# define MIN_VAL 60

typedef pthread_mutex_t	t_fork;

typedef struct s_philo {
	pthread_t			thread;	
	int32_t				state;
	int32_t				id;
	int32_t				meal_count;
	int64_t				last_meal;
	t_fork				*fork_l;
	t_fork				*fork_r;
	bool				is_full;
	int8_t				(*eat_func)(struct s_philo *);
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		state_mutex;
	struct s_simulation	*sim;
}	t_philo;

typedef struct s_simulation {
	pthread_t			monitor;
	t_philo				*philo;
	t_fork				*forks;
	bool				terminate;
	pthread_mutex_t		term_mutex;
	pthread_mutex_t		start_sim_mutex;
	pthread_mutex_t		msg_mutex;
	int64_t				start_time;
	int32_t				number_of_philosophers;
	int32_t				time_to_die;
	int32_t				time_to_eat;
	int32_t				time_to_sleep;
	int32_t				number_of_times_each_philosopher_must_eat;
	int32_t				delay;
}	t_simulation;

//###############################################################
//			SOURCE FILES	
//###############################################################

//			utils_time.c
int64_t		time_ellapsed_in_ms(int64_t start_time, int64_t end_time);
int64_t		get_time(void);
int8_t		ft_sleep(int64_t ms);

//			init_data.c
int8_t		init_simulation_data(int argc, char *argv[], t_simulation *sim);

//			philo_threads.c
int8_t		print_action(t_philo *philo, const char *msg);
void		*philo_routine(void *arg);

//			monitor_thread.c
void		monitor_routine(t_simulation *sim);

//			mutex_management.c
int8_t		init_mutex_data(t_simulation *sim);
int8_t		destroy_mutex_data(t_simulation *sim);

//			eat_routines.c
int8_t		plural_eat_routine(t_philo *philo);
int8_t		plural_eat_routine2(t_philo *philo);
int8_t		singular_eat_routine(t_philo *philo);

//			thread_management.c
int8_t		create_philo_threads(t_simulation *sim);
int8_t		join_philo_threads(t_simulation *sim);

//			utils_misc.c
int8_t		print_action(t_philo *philo, const char *msg);
void		clean_simulation_data(t_simulation *sim);
int8_t		error(const char *msg, int8_t err);
int8_t		ft_isdigit_2d(char *arr[]);
void		clean_threads(t_simulation *sim, int16_t n);

//			utils_init.c
int32_t		ft_atoi_overflow(const char *str, int8_t *err);
int8_t		set_sim_rules(t_simulation *sim, char *argv[]);

#endif
