/*
 * author : prife (goprife@gmail.com)
 * date   : 2013/01/14 01:18:50
 * version: v 0.1.0
 */
#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>

//#define TRACE       printf
#define TRACE(...)

typedef struct _thread
{
    pthread_t pthread;
    void (*task)(void *);
    void *para;
    void (*exit)(void);
    sem_t sem;
    rt_thread_t rtthread;
    void *data;
} thread_t;

#define THREAD_T(thread)  ((thread_t *)thread)

#define MSG_SUSPEND  SIGUSR1    /* 10 */
/* #define MSG_RESUME   SIGUSR2 */
#define MSG_TICK     SIGALRM    /* 14 */
#define TIMER_TYPE   ITIMER_REAL
#define MAX_INTERRUPT_NUM ((unsigned int)sizeof(unsigned int) * 8)

#define INTERRUPT_ENABLE   0
#define INTERRUPT_DISABLE  1
/* interrupt flag, if 1, disable, if 0, enable */
static long interrupt_disable_flag;

/* flag in interrupt handling */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/* interrupt event mutex */
static pthread_mutex_t *ptr_int_mutex;
static pthread_cond_t cond_int_hit; /* interrupt occured! */
static volatile unsigned int  cpu_pending_interrupts;
static int (* cpu_isr_table[MAX_INTERRUPT_NUM])(void) = {0};

static pthread_t mainthread_pid;

/* function definition */
static void start_sys_timer(void);
static int tick_interrupt_isr(void);
static void mthread_signal_tick(int sig);
static int mainthread_scheduler(void);

int signal_install(int sig, void (*func)(int))
{
    struct sigaction act;

    /* set the signal handler */
    act.sa_handler = func ;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(sig, &act, 0);
}

int signal_mask(void)
{
    sigset_t  sigmask, oldmask;

    /* set signal mask */
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGALRM);
    pthread_sigmask(SIG_BLOCK, &sigmask, &oldmask);
}
static void thread_switch_handler(int sig)
{
    pthread_t pid = pthread_self();
    thread_t *thread_from;
    thread_t *thread_to;
    rt_thread_t tid;

    if (sig != MSG_SUSPEND)
    {
        printf("get an unexpected signal <%d>, exit\n", sig);
        exit(EXIT_FAILURE);
    }

    thread_from = (thread_t *) rt_interrupt_from_thread;
    thread_to = (thread_t *) rt_interrupt_to_thread;

    /* FIXME 注意！此时 rt_thread_self的值是to线程的值！ */
    tid = rt_thread_self();
    RT_ASSERT(thread_from->pthread == pid);
    RT_ASSERT((thread_t *)(tid->sp) == thread_to);

    TRACE("signal: SIGSUSPEND suspend <%s>\n", thread_from->rtthread->name);
    sem_wait(&thread_from->sem);
    TRACE("signal: SIGSUSPEND resume  <%s>\n", thread_from->rtthread->name);
}

static void *thread_run(void *parameter)
{
    rt_thread_t tid;
    thread_t *thread;
    thread = THREAD_T(parameter);
    int res;

    /* FIXME set signal mask, mask the timer! */
    signal_mask();

    TRACE("pid <%08x> stop on sem...\n", (unsigned int)(thread->pthread));
    sem_wait(&thread->sem);

    tid = rt_thread_self();
    TRACE("pid <%08x> tid <%s> starts...\n", (unsigned int)(thread->pthread),
          tid->name);
    thread->rtthread = tid;
    thread->task(thread->para);
    TRACE("pid <%08x> tid <%s> exit...\n", (unsigned int)(thread->pthread),
          tid->name);
    //FIXME
    thread->exit();
    //sem_destroy(&thread->sem); //<--------------

    pthread_exit(NULL);
}
static int thread_create(
    thread_t *thread, void *task, void *parameter, void *pexit)
{
    int res;
    pthread_attr_t attr;

    thread->task = task;
    thread->para = parameter;
    thread->exit = pexit;

    if (sem_init(&thread->sem, 0, 0) != 0)
    {
        printf("init thread->sem failed, exit \n");
        exit(EXIT_FAILURE);
    }
    /* No need to join the threads. */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    /* create a posix thread */
    res = pthread_create(&thread->pthread, &attr, &thread_run, (void *)thread);
    if (res)
    {
        printf("pthread create faild, <%d>\n", res);
        exit(EXIT_FAILURE);
    }

    return 0;
}

/* resume the thread */
static int thread_resume(thread_t *thread)
{
    sem_post(& thread->sem);
}


rt_uint8_t *rt_hw_stack_init(
    void *pEntry,
    void *pParam,
    rt_uint8_t *pStackAddr,
    void *pExit)
{
    thread_t *thread;

    thread = (thread_t *)(pStackAddr - sizeof(thread_t));

    /* set the filed to zero */
    memset(thread, 0x00, sizeof(thread_t));

    thread_create(thread, pEntry, pParam, pExit);
    //TRACE("thread %x created\n", (unsigned int)thread_table[t].pthread);

    return (rt_uint8_t *) thread;
}

rt_base_t rt_hw_interrupt_disable(void)
{
    long back;

    if (ptr_int_mutex == NULL)
    {
        return 0;
    }

    pthread_mutex_lock(ptr_int_mutex);
    back = interrupt_disable_flag;
    interrupt_disable_flag = INTERRUPT_DISABLE;

    /*TODO: It may need to unmask the signal */
    return back;
}

void rt_hw_interrupt_enable(rt_base_t level)
{
    struct rt_thread * tid;
    pthread_t pid;
    thread_t *thread_from;
    thread_t *thread_to;

    if (ptr_int_mutex == NULL)
        return;

    interrupt_disable_flag = level;

    pthread_mutex_unlock(ptr_int_mutex);
    /* 如果已经中断仍然关闭 */
    if (interrupt_disable_flag)
    {
        return;
    }

    /* 表示当前中断打开, 检查是否有挂起的中断 */
    pthread_mutex_lock(ptr_int_mutex);
    if (!cpu_pending_interrupts)
    {
        pthread_mutex_unlock(ptr_int_mutex);
        return;
    }

    thread_from = (thread_t *) rt_interrupt_from_thread;
    thread_to = (thread_t *) rt_interrupt_to_thread;
    tid = rt_thread_self();
    pid = pthread_self();

    if (pid != mainthread_pid)
    {
        /* 注意这段代码是在RTT普通线程函数总函数中执行的，
         * from线程就是当前rtt线程 */
        /* 需要检查是否有挂起的中断需要处理 */
        TRACE("conswitch: P in pid<%x> ,suspend <%s>, resume <%s>!\n",
              (unsigned int)pid,
              thread_from->rtthread->name,
              thread_to->rtthread->name);

        /* 确定一下，这两个值一定是相等的！ */
        RT_ASSERT(thread_from->pthread == pid);

        /* 唤醒被挂起的线程 */
        sem_post(& thread_to ->sem);
        cpu_pending_interrupts --;

        pthread_mutex_unlock(ptr_int_mutex);

        /* 挂起当前的线程 */
        sem_wait(& thread_from->sem);
    }
    else
    {
        /* 注意这段代码是在system tick 函数中执行的，
         * 即此时位于主线程的SIGALRM信号处理函数中
         */
        TRACE("conswitch: S in pid<%x>  ,suspend <%s>, resume <%s>!\n",
              (unsigned int)pid,
              thread_from->rtthread->name,
              thread_to->rtthread->name);
        /* 挂起from线程 */
        pthread_kill(thread_from->pthread, MSG_SUSPEND);
        cpu_pending_interrupts --;

        pthread_mutex_unlock(ptr_int_mutex);

        /* 唤醒to线程 */
        sem_post(& thread_to->sem);

    }
    /*TODO: It may need to unmask the signal */
}

void rt_hw_context_switch_interrupt(rt_uint32_t from,
                                    rt_uint32_t to)
{
    rt_hw_context_switch(from, to);
}

void rt_hw_context_switch(rt_uint32_t from,
                          rt_uint32_t to)
{
    struct rt_thread * tid;
    pthread_t pid;
    thread_t *thread_from;
    thread_t *thread_to;

    RT_ASSERT(from != to);

#if 0
    //TODO: 还需要考虑嵌套切换的情况
    if (rt_thread_switch_interrupt_flag != 1)
    {
        rt_thread_switch_interrupt_flag = 1;

        // set rt_interrupt_from_thread
        rt_interrupt_from_thread = *((rt_uint32_t *)from);
    }
#endif
    rt_interrupt_from_thread = *((rt_uint32_t *)from);
    rt_interrupt_to_thread = *((rt_uint32_t *)to);

    /* 这个函数只是并不会真正执行中断处理函数，而只是简单的
     * 设置一下中断挂起标志位
     */
    pthread_mutex_lock(ptr_int_mutex);
    cpu_pending_interrupts ++;
    pthread_mutex_unlock(ptr_int_mutex);
}

void rt_hw_context_switch_to(rt_uint32_t to)
{
    //set to thread
    rt_interrupt_to_thread = *((rt_uint32_t *)(to));

    //clear from thread
    rt_interrupt_from_thread = 0;

    //set interrupt to 1
    rt_thread_switch_interrupt_flag = 0; //TODO: 还需要考虑这个嵌套切换的情况

    /* enable interrupt
     * note: NOW, there are only one interrupt in simposix: system tick */
    rt_hw_interrupt_enable(0);

    //start the main thread scheduler
    mainthread_scheduler();

    //never reach here!
    return;
}

static int mainthread_scheduler(void)
{
    int i, res;
    thread_t *thread_from;
    thread_t *thread_to;
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;

    /* save the main thread id */
    mainthread_pid = pthread_self();
    TRACE("pid <%08x> mainthread\n", (unsigned int)(mainthread_pid));

    /* install signal handler of system tick */
    signal_install(SIGALRM, mthread_signal_tick);
    /* install signal handler used to suspend itself */
    signal_install(MSG_SUSPEND, thread_switch_handler);

    /* create a mutex and condition val, used to indicate interrupts occrue */
    ptr_int_mutex = &mutex;
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(ptr_int_mutex, &mutexattr);

    /* start timer */
    start_sys_timer();

    /* FIXME: note that, cond var could not released earlier than pthread_con_wait */
    /* trigger_interrupt(CPU_INTERRUPT_YIELD); */
    thread_to = (thread_t *) rt_interrupt_to_thread;
    thread_resume(thread_to);

    for (;;)
    {
        sleep(1);
    }

    return 0;
}

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
static void start_sys_timer(void)
{
    struct itimerval itimer, oitimer;
    int us;

    RT_ASSERT(RT_TICK_PER_SECOND <= 1000000 || RT_TICK_PER_SECOND >= 1);

    us = 1000000 / RT_TICK_PER_SECOND - 1;

    TRACE("start system tick!\n");
    /* Initialise the structure with the current timer information. */
    if (0 != getitimer(TIMER_TYPE, &itimer))
    {
        TRACE("get timer failed.\n");
        exit(EXIT_FAILURE);
    }

    /* Set the interval between timer events. */
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = us;
    /* Set the current count-down. */
    itimer.it_value.tv_sec = 0;
    itimer.it_value.tv_usec = us;

    /* Set-up the timer interrupt. */
    if (0 != setitimer(TIMER_TYPE, &itimer, &oitimer))
    {
        TRACE("set timer failed.\n");
        exit(EXIT_FAILURE);
    }
}

static void mthread_signal_tick(int sig)
{
    int res;
    pthread_t pid = pthread_self();

    if (sig == SIGALRM)
    {
        TRACE("pid <%x> signal: SIGALRM enter!\n", (unsigned int)pid);

        if (pthread_mutex_trylock(ptr_int_mutex) != 0)
        {
            TRACE("try lock failed.\n");
            return;
        }
        tick_interrupt_isr();
        pthread_mutex_unlock(ptr_int_mutex);

        TRACE("pid <%x> signal: SIGALRM leave!\n", (unsigned int)pid);
    }
    else
    {
        TRACE("got an unexpected signal <%d>\n", sig);
        exit(EXIT_FAILURE);
    }
}

/* isr return value: 1, should not be masked, if 0, can be masked */
static int tick_interrupt_isr(void)
{
    TRACE("isr: systick enter!\n");
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();

    TRACE("isr: systick leave!\n");
    return 0;
}

