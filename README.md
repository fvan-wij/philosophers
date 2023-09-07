# Philosophers

### Requirements

- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are severalphilosophers, each philosopher has a fork on their left side and a fork on their rightside. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks statewith a mutex for each of them. 

### To do's

- [] Research external functions (usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock);
- [] Create function that displays time taken in ms.

### Sources


### Research

int usleep(useconds_t usec):
Returns 0 on success. On error, -1 is returned, with errno set to indicate cause of error.

int gettimeofday(struct timeval *tv, struct timezone *tz):
The tv argument is a struct timeval.
The tz argument is a struct timezone.


