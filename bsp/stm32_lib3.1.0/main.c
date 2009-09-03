#include <rtthread.h>
#include <rthw.h>
#include "stm32f10x.h"

extern int  rt_application_init(void);
extern void board_init(void);

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#elif __ICCARM__
#pragma section="HEAP"
#else
extern int __bss_end;
#endif

void rtthread_startup(void)
{
    /* show version */
    rt_show_version();

    /* init tick */
    rt_system_tick_init();

    /* init kernel object */
    rt_system_object_init();

    /* init timer system */
    rt_system_timer_init();

#ifdef RT_USING_HEAP
#ifdef __CC_ARM
    rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)0x20005000);
    //#warning Image$$RW_IRAM1$$ZI$$Limit
#elif __ICCARM__
    rt_system_heap_init(__segment_end("HEAP"), (void*)0x20005000);
#else
    /* init memory system */
    rt_system_heap_init((void*)&__bss_end, (void*)0x20005000);
#endif
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init all device */
    rt_device_init_all();

    /* init application */
    rt_application_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();
}

int main(void)
{
    rt_uint32_t UNUSED level;

    /* disable interrupt first */
    level = rt_hw_interrupt_disable();

    SystemInit();
    board_init();

    rtthread_startup();
    while (1);
}


