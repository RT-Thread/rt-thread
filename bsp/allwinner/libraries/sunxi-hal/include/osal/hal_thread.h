#ifndef SUNXI_HAL_THREAD_H
#define SUNXI_HAL_THREAD_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef CONFIG_KERNEL_FREERTOS

#include <pthread.h>
void *kthread_create(void (*threadfn)(void *data), void *data, const char *namefmt, ...);
int kthread_stop(void *thread);

#else

#include <rtthread.h>

#define HAL_THREAD_STACK_SIZE    (0x2000)
#define HAL_THREAD_PRIORITY      (    15)
#define HAL_THREAD_TIMESLICE     (    10)

void *kthread_create(void (*threadfn)(void *data), void *data, const char *namefmt, ...);
int kthread_stop(void *thread);
int kthread_start(void *thread);
int kthread_wakeup(void *thread);
int kthread_suspend(void *thread);

/**
 * kthread_run - create and wake a thread.
 * @threadfn: the function to run until signal_pending(current).
 * @data: data ptr for @threadfn.
 * @namefmt: printf-style name for the thread.
 *
 * Description: Convenient wrapper for kthread_create() followed by
 * wake_up_process().  Returns the kthread or ERR_PTR(-ENOMEM).
 */
#define kthread_run(threadfn, data, namefmt, ...)              \
({                                     \
    struct rt_thread *__k                          \
        = kthread_create(threadfn, data, namefmt, ## __VA_ARGS__); \
    if (!IS_ERR((unsigned long)__k))                   \
        rt_thread_startup(__k);                    \
    __k;                                   \
})

//#define in_interrupt(...)   rt_interrupt_get_nest()


#endif
#ifdef __cplusplus
}
#endif
#endif
