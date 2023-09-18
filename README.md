# Philosophers

### Requirements

- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are severalphilosophers, each philosopher has a fork on their left side and a fork on their rightside. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks statewith a mutex for each of them. 

### To do's

- [x] Write parser for argv arguments: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep and optional n_of_times_each_philosopher_must_eat
- [x] Research external functions (usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock);
- [x] Figure a way to create n of threads where n = amount of philosophers.
- [x] Create appropriate data structures where t_simulation contains data about the simulation rules and an array of t_philo structs where each t_philo contains data about the thread and current state. 
- [ ] Create timestamp system that displays the actions and states of each philosopher. 

### Sources


### Research

int usleep(useconds_t usec):
Returns 0 on success. On error, -1 is returned, with errno set to indicate cause of error.

int gettimeofday(struct timeval *tv, struct timezone *tz):
The tv argument is a struct timeval.
The tz argument is a struct timezone.

**Thread creation and thread joining**

- int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void* (*start_routine) (void*), void *arg) ->
Starts a new thread in the calling process. The new thread starts execution by invoking the start_routine(); 
Arg is passed as the sole argument of start_routine(), arg can be casted to the struct type pthread_mutex_t to access the mutex within the thread.
Returns 0 on succes; returns error number otherwise.

- int pthread_join(pthread_t thread, void * *retval) -> 
Waits for the thread to finish and joins it with the main thread. If the thread has already been terminated, then pthread_join returns immediately.
The thread specified by pthread_t thread, must be joinable.
Returns 0 on succes; returns error number otherwise.

P.s. Joining with a thread that has previously been joined results in undefined behaviour.
Failure to join with a thread that is joinable creates a zombie thread.
All of the threads in a process are peers and can join with any other thread in the process.

**Mutex:**
Locks a section of a code by using different states such as a locked state and an unlocked state.

- int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
Destroys and initializes a mutex.

**Race Conditions:**
Multiple threads reading and writing to the same variable, possibly causing faulty data.


