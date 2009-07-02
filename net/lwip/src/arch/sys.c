#include "lwip/opt.h"
#include <rtthread.h>

#if (NO_SYS == 0)
/* don't build if not configured for use in lwipopts.h */
#include "lwip/sys.h"
#include "lwip/def.h"
#include "lwip/memp.h"
#include "lwip/tcpip.h"

/* RT-Thread kernel object */
#define rt_list_entry(node, type, member) \
    ((type *)((char *)(node) - (unsigned long)(&((type *)0)->member)))
extern struct rt_object_information rt_object_container[];

/**
 * Wait (forever) for a message to arrive in an mbox.
 * While waiting, timeouts (for this thread) are processed.
 *
 * @param mbox the mbox to fetch the message from
 * @param msg the place to store the message
 */
void
sys_mbox_fetch(sys_mbox_t mbox, void **msg)
{
	rt_mb_recv(mbox, (rt_uint32_t *)msg, RT_WAITING_FOREVER);
}

/**
 * Wait (forever) for a semaphore to become available.
 * While waiting, timeouts (for this thread) are processed.
 *
 * @param sem semaphore to wait for
 */
void
sys_sem_wait(sys_sem_t sem)
{
	rt_sem_take(sem, RT_WAITING_FOREVER);
}

/**
 * Create a one-shot timer (aka timeout). Timeouts are processed in the
 * following cases:
 * - while waiting for a message using sys_mbox_fetch()
 * - while waiting for a semaphore using sys_sem_wait() or sys_sem_wait_timeout()
 * - while sleeping using the inbuilt sys_msleep()
 *
 * @param msecs time in milliseconds after that the timer should expire
 * @param h callback function to call when msecs have elapsed
 * @param arg argument to pass to the callback function
 */
void
sys_timeout(u32_t msecs, sys_timeout_handler h, void *arg)
{
	rt_timer_t timer;
	static int counter = 0;
	char tname[RT_NAME_MAX];

	rt_snprintf(tname, RT_NAME_MAX, "%s%d", SYS_LWIP_TIMER_NAME, counter);
	counter ++;

	/* create timer and start it */
	timer = rt_timer_create(tname, h, arg, msecs, RT_TIMER_FLAG_ONE_SHOT);
	rt_timer_start(timer);
}

/**
 * Go through timeout list (for this task only) and remove the first matching
 * entry, even though the timeout has not triggered yet.
 *
 * @note This function only works as expected if there is only one timeout
 * calling 'h' in the list of timeouts.
 *
 * @param h callback function that would be called by the timeout
 * @param arg callback argument that would be passed to h
*/
void
sys_untimeout(sys_timeout_handler h, void *arg)
{
	rt_base_t level;
	struct rt_list_node *list, *node;
	struct rt_timer *timer = RT_NULL;

	/* lock interrupt */
	level = rt_hw_interrupt_disable();

	/* find related timer */
	list = &rt_object_container[RT_Object_Class_Timer].object_list;
	for (node = list->next; node != list; node = node->next)
	{
		timer = (struct rt_timer*)(rt_list_entry(node, struct rt_object, list));
		if (timer->timeout_func == h && timer->parameter == arg)
		{
			break;
		}
	}

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

	/* remove this timer */
	if (timer != RT_NULL)
		rt_timer_delete(timer);
}

/**
 * Wait for a semaphore with timeout (specified in ms)
 *
 * @param sem semaphore to wait
 * @param timeout timeout in ms (0: wait forever)
 * @return 0 on timeout, 1 otherwise
 */
int
sys_sem_wait_timeout(sys_sem_t sem, u32_t timeout)
{
	rt_err_t err;

	if (timeout == 0) err = rt_sem_take(sem, RT_WAITING_FOREVER);
	else err = rt_sem_take(sem, timeout);

	if (err != RT_EOK) return 0;

	return 1;
}

/**
 * Sleep for some ms. Timeouts are processed while sleeping.
 *
 * @param ms number of milliseconds to sleep
 */
void
sys_msleep(u32_t ms)
{
	rt_thread_delay(ms);
}

#endif
