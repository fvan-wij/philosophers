# Philosophers

### Requirements

- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are severalphilosophers, each philosopher has a fork on their left side and a fork on their rightside. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks statewith a mutex for each of them. 

### To do's

- [x] Write parser for argv arguments: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep and optional n_of_times_each_philosopher_must_eat
- [ ] Research external functions (usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock);
- [ ] Figure a way to create n of threads where n = amount of philosophers.

### Sources


### Research

int usleep(useconds_t usec):
Returns 0 on success. On error, -1 is returned, with errno set to indicate cause of error.

int gettimeofday(struct timeval *tv, struct timezone *tz):
The tv argument is a struct timeval.
The tz argument is a struct timezone.

**Thread creation and mutex locking**
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void* (*start_routine) (void*), void *arg)*
Starts a new thread in the calling process. The new thread starts execution by invoking the start_routine(); arg is passed as the sole argument of start_routine();


pthread_join -> Waits for the thread to finish and joins it with the main thread.

**Race Conditions:**
Multiple threads reading and writing to the same variable, possibly causing faulty data.

**Mutex:**
Locks a section of a code by using different states such as a locked state and an unlocked state.

