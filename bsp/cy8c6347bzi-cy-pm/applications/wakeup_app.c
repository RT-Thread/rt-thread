#include "project.h"
#include <rtthread.h>
#include <drivers/pm.h>
#include <drivers/pin.h>
#include <drv_wakeup.h>


#define WAKEUP_APP_THREAD_STACK_SIZE        1024
#define WAKEUP_APP__THREAD_PRIORITY         RT_THREAD_PRIORITY_MAX / 3
#define WAKEUP_EVENT_BUTTON                 (1 << 0)

static rt_event_t wakeup_event;

static void led_app(void)
{
    rt_pm_request(PM_RUN_MODE_NORMAL);

    Cy_GPIO_Clr(Pin_LED_Orange_0_PORT, Pin_LED_Orange_0_NUM);
    rt_thread_mdelay(2000);
    Cy_GPIO_Set(Pin_LED_Orange_0_PORT, Pin_LED_Orange_0_NUM);

    rt_pm_release(PM_RUN_MODE_NORMAL);
}

static void wakeup_callback(void)
{
    rt_event_send(wakeup_event, WAKEUP_EVENT_BUTTON);
}

static void wakeup_init(void)
{
    wakeup_event = rt_event_create("wakup", RT_IPC_FLAG_FIFO);
    RT_ASSERT(wakeup_event != RT_NULL);

    bsp_register_wakeup(wakeup_callback);
}

static void pm_mode_init(void)
{
    /* PM_SLEEP_MODE_SLEEP: sleep mode
       PM_SLEEP_MODE_TIMER: deepsleep mode
       PM_SLEEP_MODE_SHUTDOWN: Hibernate */
    rt_pm_request(PM_SLEEP_MODE_TIMER);
    rt_pm_release(PM_SLEEP_MODE_SLEEP);
    rt_pm_release(PM_RUN_MODE_NORMAL);
}

void wakeup_app(void)
{
    /* wakup event and callback init */
    wakeup_init();
    /* pm mode init */
    pm_mode_init();

    while (1)
    {
        /* wait for wakeup event */
        if (rt_event_recv(wakeup_event,
                          WAKEUP_EVENT_BUTTON,
                          RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, RT_NULL) == RT_EOK)
        {
            led_app();
        }
    }
}

/*@}*/
