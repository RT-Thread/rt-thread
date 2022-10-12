# POSIX Interface

## Introduction to Pthreads

POSIX Threads is abbreviated as Pthreads. POSIX is the abbreviation of "Portable Operating System Interface". POSIX is a set of standards established by IEEE Computer Society to improve the compatibility of different operating systems and the portability of applications. Pthreads is a threaded POSIX standard defined in the POSIX.1c, Threads extensions (IEEE Std1003.1c-1995) standard, which defines a set of C programming language types, functions, and constants. Defined in the `pthread.h` header file and a thread library, there are about 100 APIs, all of which have a "`pthread_`" prefix and can be divided into 4 categories:

-   **Thread management**: Thread creating, detaching, joining, and setting and querying thread attributes.

-   **Mutex**: Abbreviation for "mutual exclusion", which restricts thread access to shared data and protects the integrity of shared data. This includes creating, destroying, locking, and unlocking mutex and some functions for setting or modifying mutex properties.

-   **Condition variable**: Communication between threads used to share a mutex. It includes functions such as creation, destruction, waiting condition variables, and sending signal .

-   **Read/write locks and barriers**: including the creation, destruction, wait, and related property settings of read-write locks and barriers.

POSIX semaphores are used with Pthreads, but are not part of the Pthreads standard definition and are defined in POSIX.1b, Real-time extensions (IEEE Std1003.1b-1993). Therefore the prefix of the semaphore correlation function is "`sem_`" instead of "`pthread_`".

Message queues, like semaphores, are used with Pthreads and are not part of the Pthreads standard definition and are defined in the IEEE Std 1003.1-2001 standard. The prefix of the message queue related function is "`mq_`".

|        Function Prefix        |         Function Group         |
|----------------------|----------------------|
|        `pthread_ `      | Thread itself and various related functions |
|     `pthread_attr_`    |      Thread attribute object      |
|    `Pthread_mutex_`    | Mutex                                  |
|  `pthread_mutexattr_` |     Mutex attribute object     |
|     `pthread_cond_ `   |        Conditional variable        |
|   `pthread_condattr_`  |    Condition variable attribute object    |
|    `pthread_rwlock_`   | Read-write lock                             |
|  `pthread_rwlockattr_` |     Read-write lock attribute object     |
|     `pthread_spin_`    |         Spin lock         |
|  `pthread_barrier_ `  |          Barrier          |
| `pthread_barrierattr_` | Barrier attribute object                    |
|          `sem_`         |         Semaphore         |
|          `mq_ `         |        Message queue        |

Most Pthreads functions return a value of 0 if they succeed, and an error code contained in the `errno.h` header file if unsuccessful. Many operating systems support Pthreads, such as Linux, MacOSX, Android, and Solaris, so applications written using Pthreads functions are very portable and can be compiled and run directly on many platforms that support Pthreads.

### Use POSIX in RT-Thread

Using the POSIX API interface in RT-Thread includes several parts: libc (for example, newlib), filesystem, pthread, and so on. Need to open the relevant options in rtconfig.h:

``` c
#define RT_USING_LIBC
#define RT_USING_DFS
#define RT_USING_DFS_DEVFS
#define RT_USING_PTHREADS
```

RT-Thread implements most of the functions and constants of Pthreads, defined in the pthread.h, mqueue.h, semaphore.h, and sched.h header files according to the POSIX standard. Pthreads is a sublibrary of libc, and Pthreads in RT-Thread are based on the encapsulation of RT-Thread kernel functions, making them POSIX compliant. The Pthreads functions and related functions implemented in RT-Thread are described in detail in the following sections.

## Thread

### Thread Handle

``` c
typedef rt_thread_t pthread_t;
```

`Pthread_t` is a redefinition of the `rt_thread_t` type, defined in the `pthread.h` header file. rt_thread_t is the thread handle (or thread identifier) of the RT-Thread and is a pointer to the thread control block. You need to define a variable of type pthread_t before creating a thread. Each thread corresponds to its own thread control block, which is a data structure used by the operating system to control threads. It stores some information about the thread, such as priority, thread name, and thread stack address. Thread control blocks and thread specific information are described in detail in the [Thread Management](../thread/thread.md) chapter.

### Create Thread

``` c
int pthread_create (pthread_t *tid,
                   const pthread_attr_t *attr,
                   void *(*start) (void *), void *arg);
```

| **Parameter** |                          **Description**                          |
|----------|------------------------------------------------------|
|  tid  |       Pointer to thread handle (thread identifier), cannot be NULL       |
|  attr | Pointer to the thread property, if NULL is used, the default thread property is used |
| start |                    Thread entry function address                    |
|  arg  |                The argument passed to the thread entry function                |
|**return**| ——                                 |
| 0         | succeeded |
| EINVAL  | Invalid parameter |
| ENOMEM  | Dynamic allocation of memory failed |

This function creates a pthread thread. This function dynamically allocates the POSIX thread data block and the RT-Thread thread control block, and saves the start address (thread ID) of the thread control block in the memory pointed to by the parameter tid, which can be used to operate in other threads. This thread; and the thread attribute pointed to by attr, the thread entry function pointed to by start, and the entry function parameter arg are stored in the thread data block and the thread control block. If the thread is created successfully, the thread immediately enters the ready state and participates in the scheduling of the system. If the thread creation fails, the resources occupied by the thread are released.

Thread properties and related functions are described in detail in the *Thread Advanced Programming* chapter. In general, the default properties can be used.

> After the pthread thread is created, if the thread needs to be created repeatedly, you need to set the pthread thread to detach mode, or use pthread_join to wait for the created pthread thread to finish.

#### Example Code for Creating Thread

The following program initializes two threads, which have a common entry function, but their entry parameters are not the same. Others, they have the same priority and are scheduled for rotation in time slices.

``` c
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/* Thread control block */
static pthread_t tid1;
static pthread_t tid2;

/* Function return value check */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
        printf("%s successfully!\n",str);
    }
    else
    {
        printf("%s failed! error code is %d\n",str,result);
    }
}

/* Thread entry function */
static void* thread_entry(void* parameter)
{
    int count = 0;
    int no = (int) parameter; /* Obtain the thread's entry parameters */

    while (1)
    {
        /* Printout thread count value */
        printf("thread%d count: %d\n", no, count ++);

        sleep(2);    /* Sleep for 2 seconds */
    }
}

/* User application portal */
int rt_application_init()
{
    int result;

    /* Create thread 1, the property is the default value, the entry function is thread_entry, and the entry function parameter is 1 */
    result = pthread_create(&tid1,NULL,thread_entry,(void*)1);
    check_result("thread1 created", result);

    /* Create thread 2, the property is the default value, the entry function is thread_entry, and the entry function parameter is 2 */
    result = pthread_create(&tid2,NULL,thread_entry,(void*)2);
    check_result("thread2 created", result);

    return 0;
}
```

### Detach Thread

``` c
int pthread_detach (pthread_t thread);
```

| Parameter  | Description                       |
|------|----------------------|
| thread | Thread handle (thread identifier) |
|**return**| ——                                 |
| 0         | succeeded |

Call this function, If the pthread does not finish running, set the detach state of the thread thread property to detached; when the thread thread has finished, the system will reclaim the resources occupied by the pthread thread.

Usage: The child thread calls `pthread_detach(pthread_self())` (*pthread_self()* returns the thread handle of the currently calling thread), or another thread calls `pthread_detach(thread_id)`. The separation state of the thread attributes will be described in detail later.

> Once the detach state of the thread property is set to detached, the thread cannot be waited by the pthread_join() function or re-set to detached.

#### Example Code for Detaching Thread

The following program initializes 2 threads, which have the same priority and are scheduled according to the time slice. Both threads will be set to the detached state. The 2 threads will automatically exit after printing 3 times of information. After exiting, the system will automatically reclaim its resources.

``` c
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/* Thread control block */
static pthread_t tid1;
static pthread_t tid2;

/* Function return value check */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
        printf("%s successfully!\n",str);
    }
    else
    {
        printf("%s failed! error code is %d\n",str,result);
    }
}

/* Thread 1 entry function */
static void* thread1_entry(void* parameter)
{
    int i;

    printf("i'm thread1 and i will detach myself!\n");
    pthread_detach(pthread_self());        /* Thread 1 detach itself */

    for (i = 0;i < 3;i++)    /* Cycle print 3 times */
    {
        printf("thread1 run count: %d\n",i);
        sleep(2);    /* Sleep 2 seconds */
    }

    printf("thread1 exited!\n");
    return NULL;
}

/* Thread 2 entry function */
static void* thread2_entry(void* parameter)
{
    int i;

    for (i = 0;i < 3;i++)    /* Cycle print 3 times */
    {
        printf("thread2 run count: %d\n",i);
        sleep(2);    /* Sleep 2 seconds */
    }

    printf("thread2 exited!\n");
    return NULL;
}
/* User application portal */
int rt_application_init()
{
    int result;

    /* Create thread 1, property is the default value, separation state is the default value joinable,
     * The entry function is thread1_entry and the entry function parameter is NULL */
    result = pthread_create(&tid1,NULL,thread1_entry,NULL);
    check_result("thread1 created",result);

    /* Create thread 2, the property is the default value, the separation state is the default value joinable,
     * The entry function is thread2_entry and the entry function parameter is NULL */
    result = pthread_create(&tid2,NULL,thread2_entry,NULL);
    check_result("thread2 created",result);

    pthread_detach(tid2);    /* detach thread 2 */

    return 0;
}
```

### Waiting for Thread to End

``` c
int pthread_join (pthread_t thread, void**value_ptr);
```

|    Parameter    |            **Description**       |
|----------|----------------------|
|   thread   | Thread handle (thread identifier) |
| value_ptr | User-defined pointer to store the return value of the waiting thread, which can be obtained by the function pthread_join() |
|**Return**| ——          |
| 0         | succeeded |
| EDEADLK  | Thread join itself |
| EINVAL  | Join a thread with a detached state |
| ESRCH  | Could not find the thread |

The thread calling this function blocks and waits for the thread with the joinable property to finish running and gets the return value of the thread. The address of the returned value is stored in `value_ptr` and frees the resources held by thread.

The pthread_join() and pthread_detach() functions are similar in that they are used to reclaim the resources occupied by threads after the thread running ends. A thread cannot wait for itself to end. The detached state of the thread thread must be `joinable`, and one thread only corresponds to the `pthread_join()` call. A thread with a split state of joinable will only release the resources it occupies when other threads execute `pthread_join()` on it. So in order to avoid memory leaks, all threads that will end up running, either detached or set to detached, or use pthread_join() to reclaim the resources they consume.

#### Example Code for Waiting for the Thread to End

The following program code initializes 2 threads, they have the same priority, and the threads of the same priority are scheduled according to the time slice. The separation status of the 2 thread attributes is the default value joinable, and thread 1 starts running first, and ends after printing 3 times of information. Thread 2 calls pthread_join() to block waiting for thread 1 to end, and reclaims the resources occupied by thread 1, and thread 2 prints the message every 2 seconds.

``` c
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/* Thread control block */
static pthread_t tid1;
static pthread_t tid2;

/* Function return value check */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
        printf("%s successfully!\n",str);
    }
    else
    {
        printf("%s failed! error code is %d\n",str,result);
    }
}

/* Thread 1 entry function */
static void* thread1_entry(void* parameter)
{
    int i;

    for (int i = 0;i < 3;i++)    /* Cycle print 3 times */
    {
        printf("thread1 run count: %d\n",i);
        sleep(2);    /* Sleep 2 seconds */
    }

    printf("thread1 exited!\n");
    return NULL;
}

/* Thread 2 entry function */
static void* thread2_entry(void* parameter)
{
    int count = 0;
    void* thread1_return_value;

    /* Blocking waiting thread 1 running end */
    pthread_join(tid1, NULL);

    /* Thread 2 print information to start output */
    while(1)
    {
        /* Print thread count value output */
        printf("thread2 run count: %d\n",count ++);
        sleep(2);    /* Sleep 2 seconds */
    }

    return NULL;
}

/* User application portal */
int rt_application_init()
{
    int result;
    /* Create thread 1, property is the default value, separation state is the default value joinable,
     * The entry function is thread1_entry and the entry function parameter is NULL */
    result = pthread_create(&tid1,NULL,thread1_entry,NULL);
    check_result("thread1 created",result);

    /* Create thread 2, the property is the default value, the separation state is the default value joinable,
     * The entry function is thread2_entry and the entry function parameter is NULL */
    result = pthread_create(&tid2,NULL,thread2_entry,NULL);
    check_result("thread2 created",result);

    return 0;
}
```

### Exit Thread

``` c
void pthread_exit(void *value_ptr);
```

|    *Parameter*    |          **Description**       |
|----------|---------------------------|
| value_ptr | User-defined pointer to store the return value of the waiting thread, which can be obtained by the function pthread_join() |

Calling this function by the pthread thread terminates execution, just as the process calls the exit() function and returns a pointer to the value returned by the thread. The thread exit is initiated by the thread itself.

> If the split state of the thread is joinable, the resources occupied by the thread will not be released after the thread exits. The pthread_join() function must be called to release the resources occupied by the thread.

#### Example Code for Exiting Thread

This program initializes 2 threads, they have the same priority, and the threads of the same priority are scheduled according to the time slice. The separation state of the two thread attributes is the default value joinable, and thread 1 starts running first, sleeps for 2 seconds after printing the information once, and then prints the exit information and then ends the operation. Thread 2 calls pthread_join() to block waiting for thread 1 to end, and reclaims the resources occupied by thread 1, and thread 2 prints the message every 2 seconds.

``` c
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/* Thread control block */
static pthread_t tid1;
static pthread_t tid2;

/* Function return value check function */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
        printf("%s successfully!\n",str);
    }
    else
    {
        printf("%s failed! error code is %d\n",str,result);
    }
}

/* Thread 1 entry function */
static void* thread1_entry(void* parameter)
{
    int count = 0;
    while(1)
    {
        /* Print thread count value output */
        printf("thread1 run count: %d\n",count ++);
        sleep(2);    /* Sleep 2 seconds */
        printf("thread1 will exit!\n");

        pthread_exit(0);    /* Thread 1 voluntarily quits */
    }
}

/* Thread 2 entry function */
static void* thread2_entry(void* parameter)
{
    int count = 0;

    /* The block waits for thread 1 to finish running */
    pthread_join(tid1,NULL);
    /* Thread 2 starts outputting print information */
    while(1)
    {
        /* Print thread count value output */
        printf("thread2 run count: %d\n",count ++);
        sleep(2);    /* Sleep 2 seconds */
    }
}

/* User application portal */
int rt_application_init()
{
    int result;

    /* Create thread 1, property is the default value, separation state is the default value joinable,
     * The entry function is thread1_entry and the entry function parameter is NULL */
    result = pthread_create(&tid1,NULL,thread1_entry,NULL);
    check_result("thread1 created",result);

    /* Create thread 2, the property is the default value, the separation state is the default value joinable,
     * The entry function is thread2_entry and the entry function parameter is NULL */
    result = pthread_create(&tid2,NULL,thread2_entry,NULL);
    check_result("thread2 created",result);

    return 0;
}
```

## Mutex

Mutexes, also known as mutually exclusive semaphores, are a special binary semaphore. Mutexes are used to ensure the integrity of shared resources. Only one thread can access the shared resource at any time. To access shared resources, the thread must first obtain the mutex. After the access is complete, the mutex must be released. Embedded shared resources include memory, IO, SCI, SPI, etc. If two threads access shared resources at the same time, there may be problems because one thread may use the resource while another thread modifies the shared resource and consider sharing.

There are only two kinds of operations of mutex,  locking or unlocking, and only one thread holds a mutex at a time. When a thread holds it, the mutex is latched and its ownership is obtained by this thread. Conversely, when this thread releases it, it unlocks the mutex and loses its ownership. When a thread holds a mutex, other threads will not be able to unlock it or hold it.

The main APIs of the mutex include: calling `pthread_mutex_init()` to initialize a mutex, `pthread_mutex_destroy()` to destroy the mutex, pthread_mutex_lock() to lock the mutex, and `pthread_mutex_unlock()` to unlock the mutex.

The rt-thread operating system implements a priority inheritance algorithm to prevent priority inversion.Priority inheritance is the practice of raising the priority of a low-priority thread that occupies a resource to the same level as the highest-priority thread of all the threads waiting for the resource, then executing, and then returning to the initial setting when the low-priority thread releases the resource.Thus, threads that inherit priority prevent system resources from being preempted by any intermediate priority thread.

For a detailed introduction to priority reversal, please refer to the [Inter-thread Synchronization](../thread-sync/thread-sync.md) Mutex section.

### Mutex Lock Control Block

Each mutex corresponds to a mutex control block that contains some information about the control of the mutex. Before creating a mutex, you must first define a variable of type `pthread_mutex_t`. pthread_mutex_t is a redefinition of pthread_mutex. The pthread_mutex data structure is defined in the pthread.h header file. The data structure is as follows:

``` c
struct pthread_mutex
{
    pthread_mutexattr_t attr;    /* Mutex attribute */
    struct rt_mutex lock;        /* RT-Thread Mutex lock control block */
};
typedef struct pthread_mutex pthread_mutex_t;

//rt_mutex is a data structure defined in the RT-Thread kernel, defined in the rtdef.h header file. The data structure is as follows:

struct rt_mutex
{
    struct rt_ipc_object parent;                 /* Inherited from the ipc_object class */
    rt_uint16_t          value;                  /* Mutex value */
    rt_uint8_t           original_priority;      /* thread's original priority */
    rt_uint8_t           hold;                   /* Mutex lock holding count  */
    struct rt_thread    *owner;                  /* Thread that currently has a mutex */
};
typedef struct rt_mutex* rt_mutex_t;             /* Rt_mutext_t is a pointer to the mutex structure */
```

### Initialize the Mutex

``` c
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
```

| **Parameter** |                          **Description**                          |
|----------|------------------------------------------------------|
| mutex |                 Mutex lock handle, cannot be NULL                 |
|  attr | Pointer to the mutex attribute, if the pointer is NULL, the default attribute is used. |
|**return**| ——          |
| 0         | succeeded |
| EINVAL  | Invalid parameter |

This function initializes the mutex `mutex` and sets the mutex property according to the mutex attribute object pointed to by `attr`. After successful initialization, the mutex is unlocked and the thread can obtain it. This function encapsulates the rt_mutex_init() function.

In addition to calling the pthread_mutex_init() function to create a mutex, you can also statically initialize the mutex with the macro PTHREAD_MUTEX_INITIALIZER by: `pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER` (structure constant), which is equivalent to specifying attr to NULL when calling pthread_mutex_init().

The mutex lock properties and related functions are described in detail in the *thread advanced programming* chapter. In general, the default properties can be used.

### Destroy Mutex

``` c
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

| **Parameter** |          **Description**          |
|----------|----------------------|
| mutex | Mutex lock handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Mutex is empty or mutex has been destroyed |
| EBUSY  | Mutex is being used |

This function destroys the mutex `mutex`. Mutex is mutable in an uninitialized state after destruction. After destroying the mutex's properties and control block parameters will not be valid, but you can call pthread_mutex_init() to reinitialize the destroyed mutex. However, there is no need to destroy the mutex that is statically initialized with the macro PTHREAD_MUTEX_INITIALIZER.

The mutex can be destroyed when it is determined that the mutex is not locked and no thread is blocked on the mutex.

### Blocking Mode Locks the Mutex

``` c
int pthread_mutex_lock(pthread_mutex_t *mutex);
```

| **Parameter** |          **Description**          |
|----------|----------------------|
| mutex | Mutex lock handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |
| EDEADLK  | Mutexes mutex do not call this function repeatedly for a thread with a nested lock |

This function locks the mutex `mutex`, which is a wrapper of the rt_mutex_take() function. If the mutex has not been locked yet, the thread applying for the mutex will successfully lock the mutex. If the mutex has been locked by the current thread and the mutex type is a nested lock, the mutex's holding count is incremented by one, and the current thread will not suspend waiting (deadlock), but the thread must corresponds to the same number of unlocks. If the mutex is held by another thread, the current thread will be blocked until the other thread unlocks the mutex, and the thread waiting for the mutex will acquire the mutex according to the *first in first out* principle. .

### Non-blocking Mode Locks the Mutex

``` c
int pthread_mutex_trylock(pthread_mutex_t *mutex);
```

| **Parameter** |          **Description**          |
|----------|----------------------|
| mutex | Mutex lock handle, cannot be NULL |
|**return**| ——          |
| 0         | succeeded |
| EINVAL  | Invalid parameter |
| EDEADLK  | Mutexes are not nested locks, but threads call this function repeatedly |
| EBUSY  | Mutexes mutex has been locked by other threads |

This function is a non-blocking version of the pthread_mutex_lock() function. The difference is that if the mutex has been locked, the thread will not be blocked, but the error code will be returned immediately.

### Unlock the Mutex

``` c
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

| Parameter |          **Description**          |
|----------|----------------------|
| mutex | Mutex lock handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |
| EPERM  | This function is called repeatedly by a thread when the mutex is not a nested lock |
| EBUSY  | Unlock the mutex held by other threads with the type of error detection lock |

Calling this function to unlock the mutex. This function is a wrapper of the rt_mutex_release() function. When the thread completes the access of the shared resource, it should release the possessed mutex as soon as possible, so that other threads can acquire the mutex in time. Only a thread that already has a mutex can release it, and its holding count is decremented by one each time the mutex is released. When the mutex's holding count is zero (ie, the holding thread has released all holding operations), the mutex becomes available, and the thread waiting on the mutex is placed in a first-in-first-out manner.  If the thread's run priority is promoted by the mutex lock, then when the mutex is released, the thread reverts to the priority before holding the mutex.

### Example Code for Mutex Lock

This program will initialize 2 threads, they have the same priority, 2 threads will call the same printer() function to output their own string, the printer() function will output only one character at a time, then sleep for 1 second, call printer The thread of the () function also sleeps. If you do not use a mutex, thread 1 prints a character, and after hibernation, thread 2 is executed, and thread 2 prints a character, so that the thread 1 and thread 2 strings cannot be completely printed, and the printed string is confusing. If a mutex is used to protect the print function printer() shared by 2 threads, thread 1 takes the mutex and executes the printer() print function to print a character, then sleeps for 1 second, which is switched to thread 2 because The nick lock has been locked by thread 1, and thread 2 will block until thread 1 of thread 1 is fully released and the thread 2 is woken up after the mutex is actively released.

``` c
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/* Thread control block */
static pthread_t tid1;
static pthread_t tid2;
/* Mutex lock control block */
static pthread_mutex_t mutex;
/* Thread-sharing print function */
static void printer(char* str)
{
    while(*str != 0)
    {
        putchar(*str);    /* Output one character */
        str++;
        sleep(1);    /* Sleep 1 second */
    }
    printf("\n");
}
/* Function return value check */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
        printf("%s successfully!\n",str);
    }
    else
    {
        printf("%s failed! error code is %d\n",str,result);
    }
}
/* Thread entry */
static void* thread1_entry(void* parameter)
{
    char* str = "thread1 hello RT-Thread";
    while (1)
    {
        pthread_mutex_lock(&mutex);      /* Mutex lock */

        printer(str);  /* Access shared print function */

        pthread_mutex_unlock(&mutex);  /* Unlock after access is complete */

        sleep(2);    /* Sleep 2 seconds */
    }
}
static void* thread2_entry(void* parameter)
{
    char* str = "thread2 hi world";
    while (1)
    {
        pthread_mutex_lock(&mutex);  /* The mutex locks */

        printer(str);  /* Access shared print function */

        pthread_mutex_unlock(&mutex);  /* Unlock after access is complete */

        sleep(2);    /* Sleep 2 seconds */
    }
}
/* User application portal */
int rt_application_init()
{
    int result;
    /* Initialize a mutex */
    pthread_mutex_init(&mutex,NULL);

    /* Create thread 1, the thread entry is thread1_entry, the attribute parameter is NULL, the default value is selected, and the entry parameter is NULL.*/
    result = pthread_create(&tid1,NULL,thread1_entry,NULL);
    check_result("thread1 created",result);

    /* Create thread 2, thread entry is thread2_entry, property parameter is NULL select default value, entry parameter is NULL*/
    result = pthread_create(&tid2,NULL,thread2_entry,NULL);
    check_result("thread2 created",result);

    return 0;
}
```

## Conditional Variable

A condition variable is actually a semaphore used for synchronization between threads. A condition variable is used to block a thread. When a condition is met, a condition is sent to the blocked thread. The blocking thread is woken up. The condition variable needs to be used with the mutex. The mutex is used to protect the shared data.

Condition variables can be used to inform shared data status. For example, if a thread that processes a shared resource queue finds that the queue is empty, then the thread can only wait until one node is added to the queue. After adding, a conditional variable signal is sent to activate the waiting thread.

The main operations of the condition variable include: calling `pthread_cond_init()` to initialize the condition variable, calling `pthread_cond_destroy()` to destroy a condition variable, calling `pthread_cond_wait()` to wait for a condition variable, and calling `pthread_cond_signal()` to send a condition variable.

### Condition Variable Control Block

Each condition variable corresponds to a condition variable control block, including some information about the operation of the condition variable. A `pthread_cond_t` condition variable control block needs to be defined before initializing a condition variable. `pthread_cond_t` is a redefinition of the `pthread_cond` structure type, defined in the pthread.h header file.

``` c
struct pthread_cond
{
    pthread_condattr_t attr;        /* Condition variable attribute */
    struct rt_semaphore sem;        /* RT-Thread semaphore control block */
};
typedef struct pthread_cond pthread_cond_t;

Rt_semaphore is a data structure defined in the RT-Thread kernel. It is a semaphore control block defined in the rtdef.h header file.

struct rt_semaphore
{
   struct rt_ipc_object parent; /* Inherited from the ipc_object class */
   rt_uint16_t value;           /* Semaphore value  */
};
```

### Initialization Condition Variable

``` c
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
```

| **Parameter** |                       **Description**                       |
|----|------------------------------------------------|
| cond |             Conditional variable handle, cannot be NULL             |
| attr | Pointer to the condition variable property, if NULL then use the default property value |
|**return**| ——          |
| 0         | succeeded |
| EINVAL  | Invalid parameter |

This function initializes the `cond` condition variable and sets its properties according to the condition variable property pointed to by `attr` , which is a wrapper of the `rt_sem_init()` function, based on semaphore implementation. The condition variable is not available after successful initialization.

You can also statically initialize a condition variable with the macro PTHREAD_COND_INITIALIZER by: `pthread_cond_t cond = PTHREAD_COND_INITIALIZER` (structural constant), which is equivalent to specifying NULL when calling `pthread_cond_init()`.

Attr General setting NULL use the default value, as described in the thread advanced programming chapter.

### Destroy Condition Variables

``` c
int pthread_cond_destroy(pthread_cond_t *cond);
```

| **Parameter** |           **Description**           |
|----|------------------------|
| cond | Conditional variable handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |
| EPERM  | Mutexes are not nested locks, but threads call this function repeatedly |
| EBUSY  | Condition variables are being used |

This function destroys the `cond` condition variable, and the `cond` is uninitialized after destruction. The attribute and control block parameters of the condition variable will not be valid after destruction, but can be reinitialized by calling `pthread_cond_init()` or statically.

Before destroying a condition variable, you need to make sure that no threads are blocked on the condition variable and will not wait to acquire, signal, or broadcast.

### Blocking Mode to Obtain Condition Variables

``` c
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
```

| **Parameter** |                **Description**                |
|----------|----------------------------------|
|  cond | Conditional variable handle, cannot be NULL        |
| mutex | Pointer to the mutex control block, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |

This function gets the `cond` condition variable in blocking mode. The thread needs to lock the mutex before waiting for the condition variable. This function first determines whether the condition variable is available. If it is not available, initializes a condition variable, then unlocks the mutex and then tries to acquire a semaphore when the semaphore's value is greater than zero, it indicates that the semaphore is available, the thread will get the semaphore, and the condition variable will be obtained, and the corresponding semaphore value will be decremented by 1. If the value of the semaphore is equal to zero, indicating that the semaphore is not available, the thread will block until the semaphore is available, after which the mutex will be locked again.

### Specify Blocking Time to Obtain Condition Variables

``` c
int pthread_cond_timedwait(pthread_cond_t *cond,
                          pthread_mutex_t *mutex,
                          const struct timespec *abstime);
```

| **Parameter**  |             **Description**                       |
|-------|-------------------------------------------------|
|   cond  | Conditional variable handle, cannot be NULL |
|  mutex  | Pointer to the mutex control block, cannot be NULL        |
| abstime | The specified wait time in operating system clock tick (OS Tick) |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |
| EPERM  | Mutexes are not nested locks, but threads call this function repeatedly |
| ETIMEDOUT  | time out |

The only difference between this function and the `pthread_cond_wait()` function is that if the condition variable is not available, the thread will be blocked for the `abstime` duration. After the timeout, the function will directly return the ETIMEDOUT error code and the thread will be woken up to the ready state.

### Send a Conditional Semaphore

``` c
int pthread_cond_signal(pthread_cond_t *cond);
```

| **Parameter** |           **Description**           |
|----|------------------------|
| cond | Conditional variable handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |

This function sends a signal and wakes up only one thread waiting for the `cond` condition variable, which encapsulates the rt_sem_release() function, which is to send a semaphore. When the value of the semaphore is equal to zero, and a thread waits for this semaphore, it will wake up the first thread waiting in the queue of the semaphore to get the semaphore. Otherwise the value of the semaphore will be increased by 1.

### Broadcast

``` c
int pthread_cond_broadcast(pthread_cond_t *cond);
```

| **Parameter** |           **Description**           |
|----|------------------------|
| cond | Conditional variable handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |

Calling this function will wake up all threads waiting for the `cond` condition variable.

### Example Code for Condition Variable

This example is a producer consumer model with a producer thread and a consumer thread that have the same priority. The producer will produce a number every 2 seconds, put it in the list pointed to by the `head`, and then call pthread_cond_signal() to send signal to the consumer thread to inform the consumer that there is data in the thread list. The consumer thread calls pthread_cond_wait() to wait for the producer thread to send a signal.

``` c
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Statically initialize a mutex and a condition variable */
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/* Pointer to the thread control block */
static pthread_t tid1;
static pthread_t tid2;

/* Function return value check */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
        printf("%s successfully!\n",str);
    }
    else
    {
        printf("%s failed! error code is %d\n",str,result);
    }
}

/* The structure data produced by the producer is stored in the linked list. */
struct node
{
    int n_number;
    struct node* n_next;
};
struct node* head = NULL; /* Link header, is a shared resource */

/* Consumer thread entry function */
static void* consumer(void* parameter)
{
    struct node* p_node = NULL;

    pthread_mutex_lock(&mutex);    /* Lock on mutex */

    while (1)
    {
        while (head == NULL)    /* Determine if there are elements in the list */
        {
            pthread_cond_wait(&cond,&mutex); /* Try to get a condition variable */
        }
        /*
        Pthread_cond_wait() will unlock the mutex first, then block in the wait queue until the fetch condition variable is awakened. After being woken up, the thread will lock the mutex again and successfully enter the critical section.
        */

        p_node = head;    /* Obtain resources */
        head = head->n_next;    /* Header pointing to the next resource */
        /* Printout */
        printf("consume %d\n",p_node->n_number);

        free(p_node);    /* Release the memory occupied by the node after obtaining the resource */
    }
    pthread_mutex_unlock(&mutex);    /* Release the mutex */
    return 0;
}
/* Producer thread entry function */
static void* product(void* patameter)
{
    int count = 0;
    struct node *p_node;

    while(1)
    {
        /* Dynamically allocate a block of structured memory */
        p_node = (struct node*)malloc(sizeof(struct node));
        if (p_node != NULL)
        {
            p_node->n_number = count++;
            pthread_mutex_lock(&mutex);    /* To operate on the critical resource head, lock it first */

            p_node->n_next = head;
            head = p_node;    /* Insert data into the list header */

            pthread_mutex_unlock(&mutex);    /* Unlock */
            printf("produce %d\n",p_node->n_number);

            pthread_cond_signal(&cond);    /* send a Signal to wake up  a thread */

            sleep(2);    /* Sleep 2 seconds */
        }
        else
        {
            printf("product malloc node failed!\n");
            break;
        }
    }
}

int rt_application_init()
{
    int result;

    /* Create a producer thread, the property is the default value, the entry function is product, and the entry function parameter is NULL*/
    result = pthread_create(&tid1,NULL,product,NULL);
    check_result("product thread created",result);

    /* Create a consumer thread, the property is the default value, the entry function is consumer, and the entry function parameter is NULL */
    result = pthread_create(&tid2,NULL,consumer,NULL);
    check_result("consumer thread created",result);

    return 0;
}
```

## Read-write Lock

Read-write locks are also known as multi-reader single-writer locks. The read-write lock divides the visitors of the shared resource into readers and writers. The reader only reads and accesses the shared resources, and the writer needs to write the shared resources. Only one thread can occupy the read-write lock of the write mode at the same time, but there can be multiple threads simultaneously occupying the read-write lock of the read mode. Read-write locks are suitable for reading data structures much more often than writes because read patterns can be shared when locked, and write mode locks are exclusive.

Read-write locks are usually implemented based on mutex locks and condition variables. A thread can lock a read-write lock several times, and it must also have the corresponding number of unlocks.

The main operations of the read-write lock include: calling `pthread_rwlock_init()` to initialize a read-write lock, the write thread calling `pthread_rwlock_wrlock()` to lock the read-write lock, and the read thread calling `pthread_rwlock_rdlock()` to lock the read-write lock , when this read-write lock is not required, calling `pthread_rwlock_destroy()` to destroys the read-write lock.

### Read-write Lock Control Block

Each read-write lock corresponds to a read-write lock control block, including some information about the operation of the read-write lock. `pthread_rwlock_t` is a redefinition of the `pthread_rwlock` data structure, defined in the `pthread.h` header file. Before creating a read-write lock, you need to define a data structure of type `pthread_rwlock_t`.

``` c
struct pthread_rwlock
{
    pthread_rwlockattr_t attr;        /* Read-write lock attribute */
    pthread_mutex_t rw_mutex;         /* Mutex lock */
    pthread_cond_t rw_condreaders;    /* Conditional variables for the reader thread to use */
    pthread_cond_t rw_condwriters;    /* Conditional variable for the writer thread to use */
    int rw_nwaitreaders;    /* Reader thread waiting to count */
    int rw_nwaitwriters;    /* Writer thread waiting to count */
    /* Read-write lock value, value 0: unlocked, value -1: is locked by the writer thread, greater than 0 value: locked by the reader thread */
    int rw_refcount;
};
typedef struct pthread_rwlock pthread_rwlock_t;     /* Type redefinition */
```

### Initialize Read-write Lock

``` c
int pthread_rwlock_init (pthread_rwlock_t *rwlock,
                            const pthread_rwlockattr_t *attr);
```

|  **Parameter**  |          **Description**                    |
|------|-------------------------------------------|
| rwlock | Read-write lock handle, cannot be NULL           |
|  attr  | Pointer to the read-write lock property, RT-Thread does not use this variable |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |

This function initializes an `rwlock` read-write lock. This function initializes the semaphore and condition variables of the read-write lock control block with default values, and the associated count parameter is initially 0. The read-write lock after initialization is in an unlocked state.

You can also use the macro PTHREAD_RWLOCK_INITIALIZER to statically initialize the read-write lock by: `pthread_rwlock_t mutex = PTHREAD_RWLOCK_INITIALIZER` (structural constant), which is equivalent to specifying `attr` a NULL value when calling pthread_rwlock_init().

`attr` generally sets NULL to the default value, as described in the chapter on advanced threading.

### Destroy Read-write Lock

``` c
int pthread_rwlock_destroy (pthread_rwlock_t *rwlock);
```

|  **Parameter**  |          **Description**          |
|------|----------------------|
| rwlock | Read-write lock handle, cannot be NULL                       |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |
| EBUSY  | The read-write lock is currently being used or has a thread waiting for the read-write lock |
| EDEADLK  | Deadlock |

This function destroys a `rwlock` read-write lock, which destroys the mutex and condition variables in the read-write lock. After the destruction, the properties of the read-write lock and the control block parameters will not be valid, but you can call pthread_rwlock_init() or re-initialize the read-write lock in static mode.

### Read-Lock of Read-Write Lock

#### Blocking mode Read-lock the read-write locks

``` c
int pthread_rwlock_rdlock (pthread_rwlock_t *rwlock);
```

|  **Parameter**  |          **Description**          |
|------|----------------------|
| rwlock | Read-write lock handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |
| EDEADLK  | Deadlock |

The reader thread can call this function to read-lock the `rwlock` read-write lock. If the read-write lock is not write-locked and no writer thread is blocked on the read-write lock, the read-write thread will successfully acquire the read-write lock. If the read-write lock has been write-locked, the reader thread will block until the thread that executes the write-lock unlocks the read-write lock.

#### Non-blocking Mode Read-lock Read-write Locks

``` c
int pthread_rwlock_tryrdlock (pthread_rwlock_t *rwlock);
```

|  **Parameter**  |          **Description**          |
|------|----------------------|
| rwlock | Read-write lock handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |
| EBUSY  | The read-write lock is currently being used or has a thread waiting for the read-write lock |
| EDEADLK  | Deadlock |

This function differs from the pthread_rwlock_rdlock() function in that if the read-write lock is already write-locked, the reader thread is not blocked, but instead returns an error code EBUSY.

#### Specify Blocking Time for the Read-write Lock to be Read-Locked

``` c
int pthread_rwlock_timedrdlock (pthread_rwlock_t *rwlock,
                                const struct timespec *abstime);
```

| **Parameter**  |             **Description**                       |
|-------|-------------------------------------------------|
|  rwlock | Read-write lock handle, cannot be NULL              |
| abstime | The specified wait time in operating system clock tick (OS Tick) |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter                                            |
| ETIMEDOUT  | Time out |
| EDEADLK  | Deadlock |

The difference between this function and the pthread_rwlock_rdlock() function is that if the read-write lock has been write-locked, the reader thread will block the specified abstime duration. After the timeout, the function will return the error code ETIMEDOUT and the thread will be woken up to the ready state.

### Write-Lock of Read-Write Lock

#### Blocking Mode Write-Locks a Read-write Lock

``` c
int pthread_rwlock_wrlock (pthread_rwlock_t *rwlock);
```

|  **Parameter**  |          **Description**          |
|------|----------------------|
| rwlock | Read-write lock handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |
| EDEADLK  | Deadlock |

The writer thread calls this function to write-lock the `rwlock` read-write lock. A write-lock read-write lock is similar to a mutex, and only one thread can write-lock a read-write lock at a time. If no thread locks the read-write lock, that is, the read-write lock value is 0, the writer thread that calls this function will write-lock the read-write lock, and other threads cannot acquire the read-write lock at this time. If there is already a thread locked the read-write lock, ie the read/write lock value is not 0, then the writer thread will be blocked until the read-write lock is unlocked.

#### Non-blocking Mode Write-Lock a Read-write Lock

``` c
int pthread_rwlock_trywrlock (pthread_rwlock_t *rwlock);
```

|  **Parameter**  |          **Description**          |
|------|----------------------|
| rwlock | Read-write lock handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter                                            |
| EBUSY  | The read-write lock is currently Write-Locked  or there are reader threads blocked on the read-write lock |
| EDEADLK  | Deadlock |

The only difference between this function and the pthread_rwlock_wrlock() function is that if a thread has locked the read-write lock, ie the read-write lock value is not 0, the writer thread that called the function will directly return an error code, and the thread will not be Blocked.

#### Specify Blocking Time for the Read-write Lock to be Write-Lock

``` c
int pthread_rwlock_timedwrlock (pthread_rwlock_t *rwlock,
                                const struct timespec *abstime);
```

|      **Parameter**      |            **Description**         |
|--------------|---------------------|
| rwlock abstime | Read-write lock handle, cannot specify the wait time for NULL, the unit is the operating system clock beat (OS Tick) |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |
| ETIMEDOUT  | Time out |
| EDEADLK  | Deadlock |

The only difference between this function and the pthread_rwlock_wrlock() function is that if a thread locks the read-write lock, that is, the read-write lock value is not 0, the calling thread blocks the specified `abstime` duration. After the timeout, the function returns the error code ETIMEDOUT, and the thread will be woken up to the ready state.

### Unlock the Read-write Lock

``` c
int pthread_rwlock_unlock (pthread_rwlock_t *rwlock);
```

|  **Parameter**  |          **Description**          |
|------|----------------------|
| rwlock | Read-write lock handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |
| EDEADLK  | Deadlock |

This function unlocks the `rwlock` read-write lock. A thread locks the same read-write lock multiple times and must have the same number of unlocks. If multiple threads wait for the read-write lock to lock after unlocking, the system will activate the waiting thread according to the first-in-first-out rule.

### Example Code for Read-write Lock

This program has two reader threads, one reader thread. The two reader threads read-lock the read-write lock first, then sleep for 2 seconds. This time the other reader threads can read-lock the read-write lock, and then read the shared data.

``` c
#include <pthread.h>
#include <sched.h>
#include <stdio.h>

/* Thread control block */
static pthread_t reader1;
static pthread_t reader2;
static pthread_t writer1;
/* Shared data book */
static int book = 0;
/* Read-write lock */
static pthread_rwlock_t rwlock;
/* Function result check */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
        printf("%s successfully!\n",str);
    }
    else
    {
        printf("%s failed! error code is %d\n",str,result);
    }
}
/* Thread entry */
static void* reader1_entry(void* parameter)
{
    while (1)
    {

        pthread_rwlock_rdlock(&rwlock);  /* Try to read-lock the read-write lock */

        printf("reader1 read book value is %d\n",book);
        sleep(2);  /* The thread sleeps for 2 seconds, switching to another thread to run */

        pthread_rwlock_unlock(&rwlock);  /* Unlock the read-write lock after the thread runs */
    }
}
static void* reader2_entry(void* parameter)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rwlock);  /* Try to read-lock the read-write lock */

        printf("reader2 read book value is %d\n",book);
        sleep(2);  /* The thread sleeps for 2 seconds, switching to another thread to run */

        pthread_rwlock_unlock(&rwlock);  /* Unlock the read-write lock after the thread runs */
    }
}
static void* writer1_entry(void* parameter)
{
    while (1)
    {
        pthread_rwlock_wrlock(&rwlock);  /* Try to write-lock the read-write lock */

        book++;
        printf("writer1 write book value is %d\n",book);

        pthread_rwlock_unlock(&rwlock);  /* Unlock the read-write lock */

        sleep(2);  /* The thread sleeps for 2 seconds, switching to another thread to run */
    }
}
/* User application portal */
int rt_application_init()
{
    int result;
    /* Default property initializes read-write lock */
    pthread_rwlock_init(&rwlock,NULL);

    /* Create a reader1 thread, the thread entry is reader1_entry, the thread attribute is the default value, and the entry parameter is NULL*/
    result = pthread_create(&reader1,NULL,reader1_entry,NULL);
    check_result("reader1 created",result);

    /* Create a reader2 thread, the thread entry is reader2_entry, the thread attribute is the default value, and the entry parameter is NULL*/
    result = pthread_create(&reader2,NULL,reader2_entry,NULL);
    check_result("reader2 created",result);

    /* Create a writer1 thread, the thread entry is writer1_entry, the thread attribute is, and the entry parameter is NULL*/
    result = pthread_create(&writer1,NULL,writer1_entry,NULL);
    check_result("writer1 created",result);

    return 0;
}
```

## Barrier

Barriers are a way to synchronize multithreading. Barrier means a barrier or railing that blocks multiple threads that arrive in the same railing until all threads arrived, then remove the railings and let them go at the same time. The thread that arrives first will block, and when all the threads that call the pthread_barrier_wait() function (the number equal to the count specified by the barrier initialization) arrive, the threads will enter the ready state from the blocked state and participate in the system scheduling again.

Barriers are implemented based on condition variables and mutex locks. The main operations include: calling `pthread_barrier_init()` to initialize a barrier, and other threads calling `pthread_barrier_wait()`. After all threads arrived, the thread wakes up to the ready state. Destroy a barrier by calling pthread_barrier_destroy() when the barrier will not be used.

### Barrier Control Block

Before creating a barrier, you need to define a `pthread_barrier_t` barrier control block. `pthread_barrier_t` is a redefinition of the `pthread_barrier` structure type, defined in the pthread.h header file.

``` c
struct pthread_barrier
{
    int count;    /* The number of waiting threads specified */
    pthread_cond_t cond;      /* Conditional variable */
    pthread_mutex_t mutex;    /* Mutex lock */
};
typedef struct pthread_barrier pthread_barrier_t;
```

### Create a Barrier

``` c
int pthread_barrier_init(pthread_barrier_t *barrier,
                        const pthread_barrierattr_t *attr,
                        unsigned count);
```

| **Parameter**  |             **Description**             |
|-------|-------------------------------|
|   attr  | Pointer to the barrier property, if passing NULL, use the default value. PTHREAD_PROCESS_PRIVATE  must be used as a non-NULL value. |
| barrier |         Barrier handle      |
|  count  | The number of waiting threads specified |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |

This function creates a `barrier` barrier and initializes the conditional variables and mutex locks of the barrier control block according to the default parameters. The number of waiting threads specified after initialization is `count`, and pthread_barrier_wait() must be called for `count` threads.

attr generally sets NULL to the default value, as described in the chapter on *thread advanced programming*.

### Destruction of Barrier

``` c
int pthread_barrier_destroy(pthread_barrier_t *barrier);
```

| **Parameter**  |   **Description**   |
|-------|--------|
| barrier | Barrier handle |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |

This function destroys a barrier. The barrier's properties and control block parameters will not be valid after destruction, but can be reinitialized by calling pthread_barrier_init().

### Wait for Barrier

``` c
int pthread_barrier_wait(pthread_barrier_t *barrier);
```

| **Parameter**  |   **Description**   |
|-------|--------|
| barrier | Barrier handle |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL  | Invalid parameter |

This function synchronizes the threads waiting in front of the barrier and called by each thread. If the number of queue waiting threads is not 0, count will be decremented by 1. If the count is 0, indicating that all threads have reached the railing. All arriving threads will be woken up and re-entered into the ready state to participate in system scheduling. If count is not 0 after the decrease, it indicates that there is still threads that do not reach the barrier, and the calling thread will block until all threads reach the barrier.

### Example Code for Barrier

This program will create 3 threads, initialize a barrier, and the barrier waits for 3 threads.  3 threads will call pthread_barrier_wait() to wait in front of the barrier. When all 3 threads are arrived, 3 threads will enter the ready state. The output count information is printed every 2 seconds.

``` c
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/* Thread control block */
static pthread_t tid1;
static pthread_t tid2;
static pthread_t tid3;
/* Barrier control block */
static pthread_barrier_t barrier;
/* Function return value check function */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
            printf("%s successfully!\n",str);
    }
    else
    {
            printf("%s failed! error code is %d\n",str,result);
    }
}
/* Thread 1 entry function */
static void* thread1_entry(void* parameter)
{
    int count = 0;

    printf("thread1 have arrived the barrier!\n");
    pthread_barrier_wait(&barrier);    /* Reach the barrier and wait for other threads to arrive */

    while (1)
    {
        /* Print thread count value output */
        printf("thread1 count: %d\n",count ++);

        /* Sleep 2 seconds */
        sleep(2);
    }
}
/* Thread 2 entry function */
static void* thread2_entry(void* parameter)
{
    int count = 0;

    printf("thread2 have arrived the barrier!\n");
    pthread_barrier_wait(&barrier);

    while (1)
    {
        /* Print thread count value */
        printf("thread2 count: %d\n",count ++);

        /* Sleep 2 seconds */
        sleep(2);
    }
}
/* Thread 3 entry function */
static void* thread3_entry(void* parameter)
{
    int count = 0;

    printf("thread3 have arrived the barrier!\n");
    pthread_barrier_wait(&barrier);

    while (1)
    {
        /* Print thread count value */
        printf("thread3 count: %d\n",count ++);

        /* Sleep 2 seconds */
        sleep(2);
    }
}
/* User application portal */
int rt_application_init()
{
    int result;
    pthread_barrier_init(&barrier,NULL,3);

    /* Create thread 1, thread entry is thread1_entry, property parameter is set to NULL, select default value, entry parameter is NULL*/
    result = pthread_create(&tid1,NULL,thread1_entry,NULL);
    check_result("thread1 created",result);

    /* Create thread 2, thread entry is thread2_entry, property parameter is set to NULL, select default value, entry parameter is NULL*/
    result = pthread_create(&tid2,NULL,thread2_entry,NULL);
    check_result("thread2 created",result);

    /* Create thread 3, thread entry is thread3_entry, property parameter is set to NULL Select default value, entry parameter is NULL*/
    result = pthread_create(&tid3,NULL,thread3_entry,NULL);
    check_result("thread3 created",result);

}
```

## Semaphore

Semaphores can be used for communication between processes and processes, or between in-process threads. Each semaphore has a semaphore value that is not less than 0, corresponding to the available amount of semaphore. Call sem_init() or sem_open() to assign an initial value to the semaphore . Call sem_post() to increment the semaphore value by 1. Call sem_wait() to decrement the semaphore value by 1. If the current semaphore is 0, call sem_wait(), the thread will suspended on the wait queue for this semaphore until the semaphore value is greater than 0 and is available.

Depending on the value of the semaphore (representing the number of available resources), POSIX semaphores can be divided into:

-   **Binary semaphore**: The value of the semaphore is only 0 and 1, and the initial value is specified as 1. This is the same as a mutex. If the resource is locked, the semaphore value is 0. If the resource is available, the semaphore value is 1. Equivalent to only one key, after the thread gets the key, after completing the access to the shared resource, you need to unlock it, put the key back, and use it for other threads that need this key. The method is the same as the mutex lock. The wait semaphore function must be used in pairs with the send semaphore function. It cannot be used alone.

-   **Count semaphore**: The value of the semaphore ranges from 0 to a limit greater than 1 (POSIX indicates that the system's maximum limit is at least 32767). This count indicates the number of available semaphores. At this point, the send semaphore function can be called separately to send the semaphore, which is equivalent to having more than one key, the thread takes a key and consumes one, and the used key does not have to be put back.

POSIX semaphores are also divided into named semaphores and unnamed semaphores:

-   A named semaphore: its value is stored in a file and is generally used for inter-process synchronization or mutual exclusion.

-   Unnamed semaphore: Its value is stored in memory and is generally used for inter-thread synchronization or mutual exclusion.

The POSIX semaphore of the RT-Thread operating system is mainly based on a package of RT-Thread kernel semaphores, mainly used for communication between threads in the system. It is used in the same way as the semaphore of the RT-Thread kernel.

### Semaphore Control Block

Each semaphore corresponds to a semaphore control block. Before creating a semaphore, you need to define a sem_t semaphore control block. Sem_t is a redefinition of the posix_sem structure type, defined in the semaphore.h header file.

``` c
struct posix_sem
{
    rt_uint16_t refcount;
    rt_uint8_t unlinked;
    rt_uint8_t unamed;
    rt_sem_t sem;    /* RT-Thread semaphore */
    struct posix_sem* next;     /* Point to the next semaphore control block */
};
typedef struct posix_sem sem_t;

Rt_sem_t is the RT-Thread semaphore control block, defined in the rtdef.h header file.

struct rt_semaphore
{
   struct rt_ipc_object parent;/* Inherited from the ipc_object class */
   rt_uint16_t value;   /* Semaphore value  */
};
/* rt_sem_t is a pointer type to the semaphore structure */
typedef struct rt_semaphore* rt_sem_t;

```

### Unnamed semaphore

The value of an unnamed semaphore is stored in memory and is generally used for inter-thread synchronization or mutual exclusion. Before using it, you must first call sem_init() to initialize it.

#### Initialize the unnamed semaphore

``` c
int sem_init(sem_t *sem, int pshared, unsigned int value);
```

| **Parameter**  |                  **Description**                  |
|-------|--------------------------------------|
|   sem   |               Semaphore handle               |
|  value  | The initial value of the semaphore, indicating the available amount of semaphore resources |
| pshared | RT-Thread unimplemented parameters          |
|**return**| ——          |
| 0         | Succeeded |
| -1  | Failed |

This function initializes an unnamed semaphore sem, initializes the semaphore related data structure according to the given or default parameters, and puts the semaphore into the semaphore list. The semaphore value after initialization is the given initial value. This function is a wrapper of the rt_sem_create() function.

#### Destroy Unnamed Semaphore

``` c
int sem_destroy(sem_t *sem);
```

| **Parameter** |    **Description**    |
|----|----------|
|  sem | Semaphore handle |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed |

This function destroys an unnamed semaphore sem and releases the resources occupied by the semaphore.

### Named Semaphore

A named semaphore whose value is stored in a file and is generally used for inter-process synchronization or mutual exclusion. Two processes can operate on named semaphores of the same name. The well-known semaphore implementation in the RT-Thread operating system is similar to the unnamed semaphore. It is designed for communication between threads and is similar in usage.

#### Create or Open a Named Semaphore

``` c
sem_t *sem_open(const char *name, int oflag, ...);
```

| **Parameter** |       **Description**       |
|----------|----------------|
|  name |    Semaphore name    |
| oflag | The way the semaphore is opened |
|**return**| ——          |
| Semaphore handle | Succeeded |
| NULL          | Failed |

This function creates a new semaphore based on the semaphore name or opens an existing semaphore. The optional values for Oflag are `0`, `O_CREAT` or `O_CREAT|O_EXCL`. If Oflag is set to `O_CREAT` , a new semaphore is created. If Oflag sets to  `O_CREAT|O_EXCL`, it returns NULL if the semaphore already exists, and creates a new semaphore if it does not exist. If Oflag is set to 0, a semaphore does not exist and NULL is returned.

#### Detach the Named Semaphore

``` c
int sem_unlink(const char *name);
```

| **Parameter** |    **Description**    |
|----|----------|
| name | Semaphore name |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed, semaphore does not exist |

This function looks up the semaphore based on the semaphore name, and marks the semaphore as a detached state if the semaphore is present. Then check the reference count. If the value is 0, the semaphore is deleted immediately. If the value is not 0, it will not be deleted until all threads holding the semaphore close the semaphore.

#### Close the Named Semaphore

``` c
int sem_close(sem_t *sem);
```

| **Parameter** |    **Description**    |
|----|----------|
|  sem | Semaphore handle |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed |

When a thread terminates,it closes the semaphore it occupies. Whether the thread terminates voluntarily or involuntarily, this closing operation is performed. This is equivalent to a reduction of 1 in the number of semaphores held. If the holding count is zero after subtracting 1 and the semaphore is in separated state, the `sem` semaphore will be deleted and the resources it occupies will be released.

### Obtain Semaphore Value

``` c
int sem_getvalue(sem_t *sem, int *sval);
```

| **Parameter** |     **Description**               |
|----|---------------------------------|
|  sem | Semaphore handle, cannot be NULL      |
| sval | Save the obtained semaphore value address, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed |

This function obtains the value of the semaphore and saves it in the memory pointed to by `sval` to know the amount of semaphore resources.

### Blocking Mode to Wait Semaphore

``` c
int sem_wait(sem_t *sem);
```

| **Parameter** |          **Description**          |
|----|----------------------|
|  sem | Semaphore handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed |

The thread calls this function to get the semaphore, which is a wrapper of the `rt_sem_take(sem,RT_WAITING_FOREVER)` function. If the semaphore value is greater than zero, the semaphore is available, the thread gets the semaphore, and the semaphore value is decremented by one. If the semaphore value is equal to 0, indicating that the semaphore is not available, the thread is blocked and entering the suspended state and queued in a first-in, first-out manner until the semaphore is available.

### Non-blocking Mode to Wait Semaphore

``` c
int sem_trywait(sem_t *sem);
```

| **Parameter** |          **Description**          |
|----|----------------------|
|  sem | Semaphore handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed |

This function is a non-blocking version of the sem_wait() function and is a wrapper of the `rt_sem_take(sem,0)` function. When the semaphore is not available, the thread does not block, but returns directly.

### Specify the Blocking Time Waiting for the Semaphore

``` c
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
```

|     **Parameter**     |             **Description**                       |
|------------|-------------------------------------------------|
|      sem     | Semaphore handle, cannot be NULL              |
| abs_timeout | The specified wait time in operating system clock tick (OS Tick) |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed |

The difference between this function and `the sem_wait()` function is that if the semaphore is not available, the thread will block the duration of `abs_timeout`. After the timeout, the function returns -1, and the thread will be awakened from the blocking state to the ready state.

### Send Semaphore

``` c
int sem_post(sem_t *sem);
```

| **Parameter** |          **Description**          |
|----|----------------------|
|  sem | Semaphore handle, cannot be NULL |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed |

This function will release a sem semaphore, which is a wrapper of the rt_sem_release() function. If the thread queue waiting for the semaphore is not empty, indicating that there are threads waiting for the semaphore, the first thread waiting for the semaphore will switch from the suspended state to the ready state, waiting for system scheduling. If no thread is waiting for the semaphore, the semaphore value will be incremented by one.

### Example Code for Unnamed Semaphore

A typical case of semaphore usage is the producer consumer model. A producer thread and a consumer thread operate on the same block of memory, the producer fills the shared memory, and the consumer reads the data from the shared memory.

This program creates 2 threads, 2 semaphores, one semaphore indicates that the shared data is empty, one semaphore indicates that the shared data is not empty, and a mutex is used to protect the shared resource. After the producer thread produces the data, it will send a `full_sem` semaphore to the consumer, informing the consumer that the thread has data available, and waiting for the `empty_sem` semaphore sent by the consumer thread after 2 seconds of sleep. The consumer thread processes the shared data after the `full_sem` sent by the producer, and sends an `empty_sem` semaphore to the producer thread after processing. The program will continue to loop like this.

``` c
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

/* Statically initialize a mutex to protect shared resources */
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/* 2 semaphore control blocks, one for resource empty signals and one for resource full signals */
static sem_t empty_sem,full_sem;

/* Pointer to the thread control block */
static pthread_t tid1;
static pthread_t tid2;

/* Function return value check */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
        printf("%s successfully!\n",str);
    }
    else
    {
        printf("%s failed! error code is %d\n",str,result);
    }
}

/* The structure data produced by the producer is stored in the linked list. */
struct node
{
    int n_number;
    struct node* n_next;
};
struct node* head = NULL; /* Link header, a shared resource */

/* Consumer thread entry function */
static void* consumer(void* parameter)
{
    struct node* p_node = NULL;

    while (1)
    {
        sem_wait(&full_sem);
        pthread_mutex_lock(&mutex);    /* Lock mutex  */

        while (head != NULL)    /* Determine if there are elements in the list */
        {
            p_node = head;    /* Obtain resources */
            head = head->n_next;    /* Header pointing to the next resource */
            /* Print */
            printf("consume %d\n",p_node->n_number);

            free(p_node);    /* Release the memory occupied by the node after getting the resource */
        }

        pthread_mutex_unlock(&mutex);    /* The critical section data operation is completed, and the mutex is released. */

        sem_post(&empty_sem);  /* Send a null semaphore to the producer */
    }
}
/* Producer thread entry function */
static void* product(void* patameter)
{
    int count = 0;
    struct node *p_node;

    while(1)
    {
        /* Dynamically allocate a block of structured memory */
        p_node = (struct node*)malloc(sizeof(struct node));
        if (p_node != NULL)
        {
            p_node->n_number = count++;
            pthread_mutex_lock(&mutex);    /* To operate on the critical resource head, lock it first */

            p_node->n_next = head;
            head = p_node;    /* Insert data into the list header */

            pthread_mutex_unlock(&mutex);    /* Unlock */
            printf("produce %d\n",p_node->n_number);

            sem_post(&full_sem);  /* Send a full semaphore to the consumer */
        }
        else
        {
            printf("product malloc node failed!\n");
            break;
        }
        sleep(2);    /* Sleep 2 seconds */
        sem_wait(&empty_sem);  /* Wait for consumers to send empty semapho */
    }
}

int rt_application_init()
{
    int result;

    sem_init(&empty_sem,NULL,0);
    sem_init(&full_sem,NULL,0);
    /* Create a producer thread, the property is the default value, the entry function is product, and the entry function parameter is NULL*/
    result = pthread_create(&tid1,NULL,product,NULL);
    check_result("product thread created",result);

    /* Create a consumer thread, the property is the default value, the entry function is consumer, and the entry function parameter is NULL */
    result = pthread_create(&tid2,NULL,consumer,NULL);
    check_result("consumer thread created",result);

    return 0;
}
```

## Message Queue

Message Queuing is another commonly used inter-thread communication method that accepts messages of unfixed length from threads or interrupt service routines and caches the messages in their own memory space. Other threads can also read the corresponding message from the message queue, and when the message queue is empty, the reader thread can be suspended. When a new message arrives, the suspended thread will be woken up to receive and process the message.

The main operations of the message queue include: creating or opening by the function `mq_open()`, calling `mq_send()` to send a message to the message queue, calling `mq_receive()` to get a message from the message queue, and when the message queue is not in use, you can call `mq_unlink()` to delete message queue.

POSIX message queue is mainly used for inter-process communication. The POSIX message queue of RT-Thread operating system is mainly based on a package of RT-Thread kernel message queue, mainly used for communication between threads in the system. It is used in the same way as the message queue of the RT-Thread kernel.

### Message Queue Control Block

Each message queue corresponds to a message queue control block. Before creating a message queue, you need to define a message queue control block. The message queue control block is defined in the mqueue.h header file.

``` c
struct mqdes
{
    rt_uint16_t refcount;  /* Reference count */
    rt_uint16_t unlinked;  /* Separation status of the message queue, a value of 1 indicates that the message queue has been separated */
    rt_mq_t mq;            /* RT-Thread message queue control block */
    struct mqdes* next;    /* Point to the next message queue control block */
};
typedef struct mqdes* mqd_t;  /* Message queue control block pointer type redefinition */
```

### Create or Open a Message Queue

``` c
mqd_t mq_open(const char *name, int oflag, ...);
```

| **Parameter** |       **Description**       |
|----------|----------------|
|  name |   Message queue name   |
| oflag | Message queue open mode |
|**return**| ——          |
| Message queue handle | Succeeded |
| NULL      | Failed |

This function creates a new message queue or opens an existing message queue based on the name of the message queue. The optional values for Oflag are `0`, `O_CREAT` or `O_CREAT\|O_EXCL`. If Oflag is set to `O_CREAT` then a new message queue is created. If Oflag sets `O_CREAT\|O_EXCL`, it returns NULL if the message queue already exists, and creates a new message queue if it does not exist. If Oflag is set to `0`, the message queue does not exist and returns NULL.

### Detach Message Queue

``` c
int mq_unlink(const char *name);
```

| **Parameter** |     **Description**     |
|----|------------|
| name | Message queue name |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed |

This function finds the message queue based on the message queue name name. If found, it sets the message queue to a detached state. If the hold count is 0, the message queue is deleted and the resources occupied by the message queue are released.

### Close the Message Queue

``` c
int mq_close(mqd_t mqdes);
```

| **Parameter** |     **Description**     |
|----------|------------|
| mqdes | Message queue handle |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed |

When a thread terminates,it closes the message queue it occupies. Whether the thread terminates voluntarily or involuntarily, this closure is performed.  This is equivalent to the message queue holding count minus 1. If the holding count is 0 after the minus 1 and the message queue is in the separated state, the `mqdes` message queue will be deleted and released the resources it occupies.

### Block Mode to Send a Message

``` c
int mq_send(mqd_t mqdes,
            const char *msg_ptr,
            size_t msg_len,
            unsigned msg_prio);
```

| **Parameter**   |                **Description**                |
|---------|----------------------------------|
|   mqdes   | Message queue handle, cannot be NULL              |
|  sg_ptr  | Pointer to the message to be sent, cannot be NULL |
|  msg_len |          The length of the message sent          |
| msg_prio | RT-Thread unimplemented this parameter   |
|**return**| ——          |
| 0         | Succeeded |
| -1        | Failed |

This function is used to send a message to the `mqdes` message queue, which is a wrapper of the rt_mq_send() function. This function adds the message pointed to by `msg_ptr` to the `mqdes` message queue, and the length of the message sent `msg_len` must be less than or equal to the maximum message length set when the message queue is created.

If the message queue is full, that is, the number of messages in the message queue is equal to the maximum number of messages, the thread that sent the message or the interrupt program will receive an error code (-RT_EFULL).

### Specify Blocking Time to Send a Message

``` c
int mq_timedsend(mqd_t mqdes,
                const char *msg_ptr,
                size_t msg_len,
                unsigned msg_prio,
                const struct timespec *abs_timeout);
```

|     **Parameter**     |             **Description**                       |
|------------|-------------------------------------------------|
|     mqdes    |              Message queue handle, cannot be NULL              |
|   msg_ptr   | Pointer to the message to be sent, cannot be NULL        |
|   msg_len   | The length of the message sent                 |
|   msg_prio  |                RT-Thread unimplemented parameters                |
| abs_timeout | The specified wait time in operating system clock tick (OS Tick) |
|**Parameter**| ——          |
| 0         | Succeeded |
| -1        | Failed |

Currently RT-Thread does not support sending messages with the specified blocking time, but the function interface has been implemented, which is equivalent to calling mq_send().

### Blocking Mode to Receive Message

``` c
ssize_t mq_receive(mqd_t mqdes,
                  char *msg_ptr,
                  size_t msg_len,
                  unsigned *msg_prio);
```

| **Parameter**   |                **Description**                |
|---------|----------------------------------|
|   mqdes   | Message queue handle, cannot be NULL              |
|  msg_ptr | Pointer to the message to be sent, cannot be NULL |
|  msg_len |          The length of the message sent          |
| msg_prio | RT-Thread unimplemented parameters        |
|**return**| ——          |
| Message length | Succeeded |
| -1        | Failed |

This function removes the oldest message from the `mqdes` message queue and puts the message in the memory pointed to by `msg_ptr`. If the message queue is empty, the thread that called the mq_receive() function will block until the message in the message queue is available.

### Specify Blocking Time to Receive Message

``` c
ssize_t mq_timedreceive(mqd_t mqdes,
                        char *msg_ptr,
                        size_t msg_len,
                        unsigned *msg_prio,
                        const struct timespec *abs_timeout);
```

|     **Parameter**     |             **Description**                       |
|------------|-------------------------------------------------|
|     mqdes    |              Message queue handle, cannot be NULL              |
|   msg_ptr   | Pointer to the message to be sent, cannot be NULL        |
|   msg_len   | The length of the message sent                 |
|   msg_prio  |                RT-Thread unimplemented parameters                |
| abs_timeout | The specified wait time in operating system clock tick (OS Tick) |
|**return**| ——          |
| Message length | Succeeded |
| -1        | Failed |

The difference between this function and the mq_receive() function is that if the message queue is empty, the thread will block the `abs_timeout` duration. After the timeout, the function will return `-1`, and the thread will be awakened from the blocking state to the ready state.

### Example Code for Message Queue

This program creates 3 threads, thread2 accepts messages from the message queue, and thread2 and thread3 send messages to the message queue.

``` c
#include <mqueue.h>
#include <stdio.h>

/* Thread control block */
static pthread_t tid1;
static pthread_t tid2;
static pthread_t tid3;
/* Message queue handle */
static mqd_t mqueue;

/* Function return value check function */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
            printf("%s successfully!\n",str);
    }
    else
    {
            printf("%s failed! error code is %d\n",str,result);
    }
}
/* Thread 1 entry function */
static void* thread1_entry(void* parameter)
{
    char buf[128];
    int result;

    while (1)
    {
        /* Receive messages from the message queue */
        result = mq_receive(mqueue, &buf[0], sizeof(buf), 0);
        if (result != -1)
        {
            /* Output content */
            printf("thread1 recv [%s]\n", buf);
        }

        /* Sleep 1 second */
       // sleep(1);
    }
}
/* Thread 2 entry function */
static void* thread2_entry(void* parameter)
{
    int i, result;
    char buf[] = "message2 No.x";

    while (1)
    {
       for (i = 0; i < 10; i++)
        {
            buf[sizeof(buf) - 2] = '0' + i;

            printf("thread2 send [%s]\n", buf);
            /* Send a message to the message queue */
            result = mq_send(mqueue, &buf[0], sizeof(buf), 0);
            if (result == -1)
            {
                /* Message queue full, delayed 1s */
                printf("thread2:message queue is full, delay 1s\n");
                sleep(1);
            }
        }

        /* Sleep 2 seconds */
        sleep(2);
    }
}
/* Thread 3 entry function */
static void* thread3_entry(void* parameter)
{
    int i, result;
    char buf[] = "message3 No.x";

    while (1)
    {
       for (i = 0; i < 10; i++)
        {
            buf[sizeof(buf) - 2] = '0' + i;

            printf("thread3 send [%s]\n", buf);
            /* Send messages to the message queue */
            result = mq_send(mqueue, &buf[0], sizeof(buf), 0);
            if (result == -1)
            {
                /* Message queue full, delayed 1s */
                printf("thread3:message queue is full, delay 1s\n");
                sleep(1);
            }
        }

        /* Sleep 2 seconds */
        sleep(2);
    }
}
/* User application portal */
int rt_application_init()
{
    int result;
    struct mq_attr mqstat;
    int oflag = O_CREAT|O_RDWR;
#define MSG_SIZE    128
#define MAX_MSG        128
    memset(&mqstat, 0, sizeof(mqstat));
    mqstat.mq_maxmsg = MAX_MSG;
    mqstat.mq_msgsize = MSG_SIZE;
    mqstat.mq_flags = 0;
    mqueue = mq_open("mqueue1",O_CREAT,0777,&mqstat);

    /* Create thread 1, thread entry is thread1_entry, property parameter is set to NULL, select default value, entry parameter is NULL*/
    result = pthread_create(&tid1,NULL,thread1_entry,NULL);
    check_result("thread1 created",result);

    /* Create thread 2, thread entry is thread2_entry, property parameter is set to NULL, select default value, entry parameter is NULL*/
    result = pthread_create(&tid2,NULL,thread2_entry,NULL);
    check_result("thread2 created",result);

    /* Create thread 3, thread entry is thread3_entry, property parameter is set to NULL Select default value, entry parameter is NULL*/
    result = pthread_create(&tid3,NULL,thread3_entry,NULL);
    check_result("thread3 created",result);


    return 0;
}
```

## Thread Advanced Programming

This section provides a detailed introduction to some of the rarely used property objects and related functions.

The thread attributes implemented by RT-Thread include thread stack size, thread priority, thread separation status, and thread scheduling policy. `pthread_create()` must initialize the property object before using the property object. APIs such as setting thread properties should be called before the thread is created. Changes of thread attributes do not affect the threads that have been created.

The thread attribute structure `pthread_attr_t` is defined in the pthread.h header file. The thread attribute structure is as follows:

``` c
/* pthread_attr_t Type redefinition */
typedef struct pthread_attr pthread_attr_t;
/* Thread attribute structure */
struct pthread_attr
{
    void*      stack_base;      /* Thread stack address */
    rt_uint32_t stack_size;     /* Thread stack size */
    rt_uint8_t priority;        /* Thread priority */
    rt_uint8_t detachstate;     /* Thread detached state */
    rt_uint8_t policy;          /* Thread scheduling policy */
    rt_uint8_t inheritsched;    /* Thread inheritance */
};
```

#### Thread Property Initialization and Deinitialization

The thread property initialization and deinitialization functions are as follows:

``` c
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
```

| **Parameter** |        **Description**        |
|----|------------------|
| attr | Pointer to the thread property |
|**return**| ——          |
| 0         | Succeeded |

Using the pthread_attr_init() function initializes the thread attribute structure `attr` with the default value, which is equivalent to setting the parameter to NULL when calling the thread initialization function. You need to define a `pthread_attr_t` attribute object before use. This function must be called before the pthread_create() function.

The pthread_attr_destroy() function deinitializes the property pointed to by `attr` and can then reinitialize this property object by calling the pthread_attr_init() function again.

#### Thread Detached State

Setting or getting the separation state of a thread  is as follows. By default, the thread is non-separated.

``` c
int pthread_attr_setdetachstate(pthread_attr_t *attr, int state);
int pthread_attr_getdetachstate(pthread_attr_t const *attr, int *state);
```

| **Parameter** | **Description**    |
|----------|-------------------|
|  attr | Pointer to the thread property |
| state | Thread detached state |
|**return**| ——          |
| 0         | Succeeded |

The thread separation state property value state can be `PTHREAD_CREATE_JOINABL` (non-detached) and `THREAD_CREATE_DETACHED` (detached).

The detached state of a thread determines how a thread reclaims the resources it occupies after the end of its run. There are two types of thread separation: joinable or detached. When the thread is created, you should call pthread_join() or pthread_detach() to reclaim the resources occupied by the thread after it finishes running. If the thread's detached state is joinable, other threads can call the pthread_join() function to wait for the thread to finish and get the thread return value, and then reclaim the resources occupied by the thread. A thread with a detached state cannot be joined by another thread. Immediately after the end of its operation, the system resources are released.

#### Thread Scheduling Policy

Setting \ Obtaining thread scheduling policy function is as follows:

``` c
int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);
int pthread_attr_getschedpolicy(pthread_attr_t const *attr, int *policy);
```

Only the function interface is implemented. The default different priorities are based on priority scheduling, and the same priority time slice polling scheduling

#### Thread Scheduling Parameter

Set / Obtain the thread's priority function as follows:

``` c
int pthread_attr_setschedparam(pthread_attr_t *attr,
                               struct sched_param const *param)；
int pthread_attr_getschedparam(pthread_attr_t const *attr,
                               struct sched_param *param)；
```

| **Parameter** |        **Description**        |
|----------|------------------|
|  attr | Pointer to the thread property |
| param | Pointer to the dispatch parameter |
|**return**| ——          |
| 0         | Succeeded |

The `pthread_attr_setschedparam()` function sets the priority of the thread. Use `param` to set the thread priority.

**Parameter** : The `struct sched_param` is defined in sched.h and has the following structure:

``` c
struct sched_param
{
    int sched_priority;    /* Thread priority */
};
```

The member  `sched_paraority`  of the `sched_param` controls the priority value of the thread.

#### Thread Stack Size

Set / Obtain the stack size of a thread is as follows:

``` c
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stack_size);
int pthread_attr_getstacksize(pthread_attr_t const *attr, size_t *stack_size);
```

| **Parameter**    |        **Description**        |
|-----------|------------------|
|     attr    | Pointer to the thread property |
| stack_size |    Thread stack size    |
|**return**| ——          |
| 0         | Succeeded |

The `pthread_attr_setstacksize()` function sets the stack size in bytes. Stack space address alignment is required on most systems (for example, the ARM architecture needs to be aligned to a 4-byte address).

#### Thread Stack Size and Address

Set / Obtain the stack address and stack size of a thread is as follows:

``` c
int pthread_attr_setstack(pthread_attr_t *attr,
                          void *stack_base,
                          size_t stack_size);
int pthread_attr_getstack(pthread_attr_t const *attr,
                          void**stack_base,
                          size_t *stack_size);
```

| **Parameter**    |        **Description**        |
|-----------|------------------|
|     attr    | Pointer to the thread property |
| stack_size |    Thread stack size    |
| stack_base |    Thread stack address    |
|**return**| ——          |
| 0         | Succeeded |

#### Thread Attribute Related Function

The function that sets / obtains the scope of the thread is as follows:

``` c
int pthread_attr_setscope(pthread_attr_t *attr, int scope)；
int pthread_attr_getscope(pthread_attr_t const *attr);
```

| **Parameter**    |        **Description**        |
|-----------|------------------|
|     attr    | Pointer to the thread property |
| scope |    Thread scope    |
|**return**| ——          |
| 0         | scope is PTHREAD_SCOPE_SYSTEM |
| EOPNOTSUPP    | scope is PTHREAD_SCOPE_PROCESS |
| EINVAL        | scope is PTHREAD_SCOPE_SYSTEM |

#### Example Code for Thread Property

This program will initialize 2 threads, they have a common entry function, but their entry parameters are not the same. The first thread created will use the provided `attr` thread attribute, and the other thread will use the system default attribute. Thread priority is a very important parameter, so this program will modify the first created thread to have a priority of 8, and the system default priority of 24.

``` c
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>

/* Thread control block */
static pthread_t tid1;
static pthread_t tid2;

/* Function return value check */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
        printf("%s successfully!\n",str);
    }
    else
    {
        printf("%s failed! error code is %d\n",str,result);
    }
}
/* Thread entry function */
static void* thread_entry(void* parameter)
{
    int count = 0;
    int no = (int) parameter; /* Obtain the thread's entry parameters */

    while (1)
    {
        /* Printout thread count value */
        printf("thread%d count: %d\n", no, count ++);

        sleep(2);    /* Sleep 2 seconds */
    }
}

/* User application portal */
int rt_application_init()
{
    int result;
    pthread_attr_t attr;      /* Thread attribute */
    struct sched_param prio;  /* Thread priority */

    prio.sched_priority = 8;  /* Priority is set to 8 */
    pthread_attr_init(&attr);  /* Initialize the property with default values first */
    pthread_attr_setschedparam(&attr,&prio);  /* Modify the priority corresponding to the attribute */

    /* Create thread 1, attribute is attr, entry function is thread_entry, and the entry function parameter is 1 */
    result = pthread_create(&tid1,&attr,thread_entry,(void*)1);
    check_result("thread1 created",result);

    /* Create thread 2, the property is the default value, the entry function is thread_entry, and the entry function parameter is 2 */
    result = pthread_create(&tid2,NULL,thread_entry,(void*)2);
    check_result("thread2 created",result);

    return 0;
}
```

### Thread Cancellation

Cancellation is a mechanism that allows one thread to end other threads. A thread can send a cancel request to another thread. Depending on the settings, the target thread may ignore it and may end immediately or postpone it until the next cancellation point.

#### Send Cancellation Request

The cancellation request can be sent using the following function:

``` c
int pthread_cancel(pthread_t thread);
```

|  **Parameter**  |   **Description**   |
|------|--------|
| thread | Thread handle |
|**return**| ——          |
| 0         | Succeeded |

This function sends a cancel request to the `thread` thread. Whether the thread will respond to the cancellation request and when it responds depends on the state and type of thread cancellation.

#### Set Cancel Status

The cancellation request can be set using the following function:

``` c
int pthread_setcancelstate(int state, int *oldstate);
```

|   **Parameter**   |       **Description**              |
|--------|-------------------------------|
|   state  | There are two values: <br />`PTHREAD_CANCEL_ENABLE`: Cancel enable. <br />`PTHREAD_CANCEL_DISABLE`: Cancel disabled (default value when thread is created). |
| oldstate | Save the original cancellation status      |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL    | state is not PTHREAD_CANCEL_ENABLE or PTHREAD_CANCEL_DISABLE |

This function sets the cancel state and is called by the thread itself. Canceling the enabled thread will react to the cancel request, and canceling the disabled thread will not react to the cancel request.

#### Set Cancellation Type

You can use the following function to set the cancellation type, which is called by the thread itself:

``` c
int pthread_setcanceltype(int type, int *oldtype);
```

| **Parameter**  |       **Description**          |
|-------|---------------------------------|
|   type  | There are 2 values: <br />`PTHREAD_CANCEL_DEFFERED`: After the thread receives the cancellation request, it will continue to run to the next cancellation point and then end. (Default value when thread is created) .<br />`PTHREAD_CANCEL_ASYNCHRONOUS`: The thread ends immediately. |
| oldtype | Save the original cancellation type |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL | state is neither PTHREAD_CANCEL_DEFFERED nor PTHREAD_CANCEL_ASYNCHRONOUS |

#### Set Cancellation Point

The cancellation point can be set using the following function:

``` c
void pthread_testcancel(void);
```

This function creates a cancellation point where the thread is called. Called primarily by a thread that does not contain a cancellation point, it can respond to a cancellation request. This function does not work if pthread_testcancel() is called while the cancel state is disabled.

#### Cancellation Point

The cancellation point is where the thread ends when it accepts the cancellation request. According to the POSIX standard, system calls that cause blocking, such as pthread_join(), pthread_testcancel(), pthread_cond_wait(), pthread_cond_timedwait(), and sem_wait(), are cancellation points.

All cancellation points included in RT-Thread are as follows:

-   mq_receive()

-   mq_send()

-   mq_timedreceive()

-   mq_timedsend()

-   msgrcv()

-   msgsnd()

-   msync()

-   pthread_cond_timedwait()

-   pthread_cond_wait()

-   pthread_join()

-   pthread_testcancel()

-   sem_timedwait()

-   sem_wait()

-   pthread_rwlock_rdlock()

-   pthread_rwlock_timedrdlock()

-   pthread_rwlock_timedwrlock()

-   pthread_rwlock_wrlock()

#### Example Code for Thread Cancel

This program creates 2 threads. After thread2 starts running, it sleeps for 8 seconds. Thread1 sets its own cancel state and type, and then prints the run count information in an infinite loop. After thread2 wakes up, it sends a cancel request to thread1, and thread1 ends the run immediately after receiving the cancel request.

``` c
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/* Thread control block */
static pthread_t tid1;
static pthread_t tid2;

/* Function return value check */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
        printf("%s successfully!\n",str);
    }
    else
    {
        printf("%s failed! error code is %d\n",str,result);
    }
}
/* Thread 1 entry function */
static void* thread1_entry(void* parameter)
{
    int count = 0;
    /* Set the cancel state of thread 1 to be enabled. The cancel type is terminated immediately after the thread receives the cancel point. */
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    while(1)
    {
        /* Print thread count value output */
        printf("thread1 run count: %d\n",count ++);
        sleep(2);    /* Sleep 2 seconds */
    }
}
/* Thread 2 entry function */
static void* thread2_entry(void* parameter)
{
    int count = 0;
    sleep(8);
    /* Send a cancel request to thread 1 */
    pthread_cancel(tid1);
    /* Waiting for thread 1 to finish in blocking mode */
    pthread_join(tid1,NULL);
    printf("thread1 exited!\n");
    /* Thread 2 print information to start output */
    while(1)
    {
        /* Print thread count value output */
        printf("thread2 run count: %d\n",count ++);
        sleep(2);    /* Sleep 2 seconds */
    }
}
/* User application portal */
int rt_application_init()
{
    int result;
    /* Create thread 1, the property is the default value, the separation state is the default value joinable, the entry function is thread1_entry, and the entry function parameter is NULL */
    result = pthread_create(&tid1,NULL,thread1_entry,NULL);
    check_result("thread1 created",result);

    /* Create thread 2, the property is the default value, the separation state is the default value joinable, the entry function is thread2_entry, and the entry function parameter is NULL */
    result = pthread_create(&tid2,NULL,thread2_entry,NULL);
    check_result("thread2 created",result);

    return 0;
}
```

### One-time Initialization

It can be initialized once using the following function:

``` c
int pthread_once(pthread_once_t * once_control, void (*init_routine) (void));
```

| **Parameter**     |   **Description**   |
|-------------|--------|
| once_control | Control variable |
| init_routine | Execute function |
|**return**| ——          |
| 0         | Succeeded |

Sometimes we need to initialize some variables only once. If we do multiple initialization procedures, it will get an error. In traditional sequential programming, one-time initialization is often managed by using Boolean variables. The control variable is statically initialized to 0, and any code that relies on initialization can test the variable. If the variable value is still 0, it can be initialized and then set the variable to 1. Codes that are checked later will skip initialization.

### Clean up after the Thread Ends

The thread cleanup function interface:

``` c
void pthread_cleanup_pop(int execute);
void pthread_cleanup_push(void (*routine)(void*), void *arg);
```

| **Parameter**  |   **Description**             |
|-------|-----------------------------|
| execute | 0 or 1, determin whether to execute the cleanup function |
| routine | Pointer to the cleanup function      |
|   arg   | The parameter passed to the cleanup function |

pthread_cleanup_push() puts the specified cleanup `routine` into the thread's cleanup function list. pthread_cleanup_pop() takes the first function from the header of the cleanup function list. If `execute` is a non-zero value, then this function is executed.

### Other Thread Related Functions

#### Determine if two Threads are Equal

``` c
int pthread_equal (pthread_t t1, pthread_t t2);
```

|    **Parameter**    |   **Description**   |
|----------|--------|
| pthread_t | Thread handle |
|**return**| ——          |
| 0         | Not equal |
| 1         | Equal |

#### Obtain Thread Handle

``` c
pthread_t pthread_self (void);
```
pthread_self() returns the handle of the calling thread.

#### Get the Maximum and Minimum Priority

``` c
int sched_get_priority_min(int policy);
int sched_get_priority_max(int policy);
```

|  **Parameter**  |     **Description**               |
|------|---------------------------------|
| policy | 2 values are optional: SCHED_FIFO, SCHED_RR |

sched_get_priority_min() returns a value of 0, with the highest priority in RT-Thread and sched_get_priority_max() with the lowest priority.

### Mutex Attribute

The mutex properties implemented by RT-Thread include the mutex type and the mutex scope.

#### Mutex Lock Attribute Initialization and Deinitialization

``` c
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
```

| **Parameter** |           **Description**           |
|----|------------------------|
| attr | Pointer to the mutex attribute object |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL        | Invalid parameter |

The pthread_mutexattr_init() function initializes the property object pointed to by `attr` with the default value, which is equivalent to setting the property parameter to NULL when calling the pthread_mutex_init() function.

The pthread_mutexattr_destroy() function will initialize the property object pointed to by `attr` and can be reinitialized by calling the pthread_mutexattr_init() function.

#### Mutex Lock Scope

``` c
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int  pshared);
int pthread_mutexattr_getpshared(pthread_mutexattr_t *attr, int *pshared);
```

| **Parameter**  |   **Description** |
|-------|--------------------|
|   type  |    Mutex type    |
| pshared | There are 2 optional values: <br />`PTHREAD_PROCESS_PRIVATE`: The default value, used to synchronize only threads in the process. `PTHREAD_PROCESS_SHARED`: Used to synchronize threads in this process and other processes. |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL        | Invalid parameter |

#### Mutex Type

``` c
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type);
```

| **Parameter** |           **Description**           |
|----|------------------------|
| type |        Mutex type        |
| attr | Pointer to the mutex attribute object |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL        | Invalid parameter |

The type of mutex determines how a thread behaves when it acquires a mutex. RT-Thread implements three mutex types:

-   **PTHREAD_MUTEX_NORMAL**: Normal lock. When a thread is locked, the remaining threads requesting the lock will form a wait queue, and after unlocking, the lock will be acquired in the first-in first-out manner. If a thread attempts to regain the mutex without first releasing the mutex, it does not generate a deadlock, but instead returns an error code, just like the error checking lock.

-   **PTHREAD_MUTEX_RECURSIVE**: Nested locks that allow a thread to successfully acquire the same lock multiple times, requiring the same number of unlocks to release the mutex.

-   **PTHREAD_MUTEX_ERRORCHECK**: Error checking lock, if a thread tries to regain the mutex without first releasing the mutex, an error is returned. This ensures that deadlocks do not occur when multiple locks are not allowed.

### Condition Variable Attribute

Use the default value PTHREAD_PROCESS_PRIVATE to initialize the condition variable attribute attr to use the following function:

``` c
int pthread_condattr_init(pthread_condattr_t *attr);
```

| **Parameter** |            **Description**            |
|----|--------------------------|
| attr | Pointer to a condition variable property object |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL        | Invalid parameter |

#### Obtain Condition Variable Scope

``` c
int pthread_mutexattr_getpshared(pthread_mutexattr_t *attr, int *pshared);
```

| **Parameter** |            **Description**            |
|----|--------------------------|
| attr | Pointer to a condition variable property object |
|**return**| ——          |
| 0         | Succeeded |
| EINVAL        | Invalid parameter |

### Read-write Lock Attribute

#### Initialize Property

``` c
int pthread_rwlockattr_init (pthread_rwlockattr_t *attr);
```

| **Parameter** |         **Description**         |
|----|--------------------|
| attr | Pointer to the read-write lock property |
|**return**| ——          |
| 0         | Succeeded |
|-1         | Invalid parameter |

This function initializes the read-write lock attribute `attr` with the default value PTHREAD_PROCESS_PRIVATE.

#### Obtain Scope

``` c
int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *attr, int *pshared);
```

| **Parameter**  |            **Description**            |
|-------|--------------------------|
|   attr  | Pointer to the read-write lock property     |
| pshared | Pointer to the scope of the read-write lock |
|**return**| ——          |
| 0         | Succeeded |
|-1         | Invalid parameter |

The memory pointed to by pshared is saved as PTHREAD_PROCESS_PRIVATE.

### Barrier Attribute

#### Initialize Property

``` c
int pthread_barrierattr_init(pthread_barrierattr_t *attr);
```

| **Parameter** |        **Description**        |
|----|------------------|
| attr | Pointer to the barrier property |
|**return**| ——          |
| 0         | Succeeded |
|-1         | Invalid parameter |

The modified function initializes the barrier attribute `attr` with the default value PTHREAD_PROCESS_PRIVATE.

#### Obtain Scope

``` c
int pthread_barrierattr_getpshared(const pthread_barrierattr_t *attr, int *pshared);
```

| **Parameter**  | **Description**              |
|-------|-----------------------------|
|   attr  | Pointer to the barrier property |
| pshared | Pointer to save barrier scope data |
|**return**| ——          |
| 0         | Succeeded |
|-1         | Invalid parameter |

### Message Queue Property

The message queue attribute control block is as follows:

``` c
struct mq_attr
{
    long mq_flags;      /* Message queue flag to indicate whether to block */
    long mq_maxmsg;     /* Message queue maximum number of messages */
    long mq_msgsize;    /* The maximum number of bytes per message in the message queue */
    long mq_curmsgs;    /* Message queue current message number */
};
```
#### Obtain Attribute
``` c
int mq_getattr(mqd_t mqdes, struct mq_attr *mqstat);
```

|  **Parameter**  |           **Description**           |
|------|------------------------|
|  mqdes | Pointer to the message queue control block |
| mqstat |  Pointer to save the get data  |
|**return**| ——          |
| 0         | Succeeded |
|-1         | Invalid parameter |
