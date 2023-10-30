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
- [x] Create timestamp system that displays the actions and states of each philosopher. 
- [x] Fix bug where the simulation sometimes starts incorrectly (too many philosophers start dining at the same time).
- [ ] Fix bug where the simulation should stop, but some philospohers still continue with their actions.
- [ ] 1 philo case.
- [ ] 200+ philo case.

### Sources
- https://github.com/rangaeeeee/books-raspberrypimagazines/blob/master/The%20Linux%20Programming%20Interface-Michael%20Kerrisk.pdf

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

**From the Linux Programming Interface (By Michael Kerrisk)**
- Threads vs. Processes
Processes have some limitations when compared to threads.
It is for instance difficult to share information between processes. Since parent and child don't share memory, you have to use some form of interprocess comunication.
Process creation with fork() is relatively expensive and time-consuming.
Threads on the other hand, can share information easy and fsat. It's just a matter of copying data into shared variables. This can however cause issues, and to avoid that, one should employ certain synchronization techniques.
Thread creation is also faster than process creation (usually 10x).

- Besides global memory, threads share a number of other attributes:
-process ID and parent process ID; 
-process group ID and session ID;
-controlling terminal;
-process credentials (user and group IDs);
-open file descriptors;
-record locks created using fcntl();
-signal dispositions;
-file system–related information: umask, current working directory, and root
directory;
-interval timers (setitimer()) and POSIX timers (timer_create());
-System V semaphore undo (semadj) values (Section 47.8);
-resource limits;
-CPU time consumed (as returned by times());
-resources consumed (as returned by getrusage()); and
-nice value (set by setpriority() and nice()).
620 Chapter 29
- Among the attributes that are distinct for each thread are the following:
-thread ID (Section 29.5);
-signal mask;
-thread-specific data (Section 31.3);
-alternate signal stack (sigaltstack());
-the errno variable;
-floating-point environment (see fenv(3));
-realtime scheduling policy and priority (Sections 35.2 and 35.3);
-CPU affinity (Linux-specific, described in Section 35.4);
-capabilities (Linux-specific, described in Chapter 39); and
-stack (local variables and function call linkage information).

- Pthreads data types
|Data type|Description|
|---------|-----------|
|pthread_t| Thread identifier|
|pthread_mutex_t|Mutex|
|pthread_mutexattr_t|Mutex attributes object|
|pthread_cond_t|Condition variable|
|pthread_condattr_t|Condition variable attributes object|
|pthread_key_t|Key for thread-specific data|
|pthread_once_t|One-time initialization control context|
|pthread_attr_t|Thread attributes object|

- Threads and errno
In threaded programs, each thread has its own errno value and can be retrieved individually per thread in the traditional UNIX manner.
All Pthreads functions return 0 on success or a positive value on failure (==errno)

- Compiling Pthread programs
On Linux, Pthread programs must be compiled with cc -pthread. The effects of this includes:
The _ REENTRANT preprocessor macro is defined. This causes the declaratoins of a few reentrant functoins to be exposed.
The program is linked with libpthread library (the equivalent of -lpthread).

- Important note on the Pthread return value
Caution is required when using a cast integer as the return value of a threads's routine function. If the value to be returned is similar to the PTHREAD_CANCELED value, it will wrongly appear that the thread was canceled.

- Critical section
A section of code that accesses a shared resource and whose execution should be atomic (itsss execution should not be interrupted by another thread that simultaneously accesses the same share resource)

- Statically vs dynamically allocating a mutex
statically -> pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
dynamically -> pthread_mutex_init(&mutex);


