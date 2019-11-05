
#include <rthw.h>
#include <rtthread.h>
#include <project.h>
#include "board.h"

extern void rt_application_init(void);

#define configTOTAL_HEAP_SIZE           (24*1024)
/* Allocate the memory for the heap. */
static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];


/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

    /* init tick */
    rt_system_tick_init();

    /* init kernel object */
    rt_system_object_init();

    /* init timer system */
    rt_system_timer_init();

    //rt_system_heap_init((void*)HEAP_BEGIN, (void*)HEAP_END);
    rt_system_heap_init((void*)ucHeap, (void*)(ucHeap+configTOTAL_HEAP_SIZE));

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

    /* init timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();
    
    /* never reach here */
    return ;
}

int rt_main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}

/*@}*/
