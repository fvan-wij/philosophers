#ifndef PHILO_H 
# define PHILO_H 

//###############################################################
//		DATA_STRUCTURES
//###############################################################

//				main struct
typedef struct 	s_philo {
				int	number_of_philosophers;
				int	time_to_die;
				int	time_to_eat;
				int	time_to_sleep;
				int	number_of_times_each_philosopher_must_eat;
}				t_philo;

//###############################################################
//		SOURCE FILES	
//###############################################################

//			main.c

//			time.c
void		print_time();
long int	delta_time(long int init_ms);

//			init.c
int 		ft_isarrnum(char *arr[]);
int			is_correct_argc(int argc);
void		init_philosophers(int argc, char *argv[], t_philo *philo);

#endif
