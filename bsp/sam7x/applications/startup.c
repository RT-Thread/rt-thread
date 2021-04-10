/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-31     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

#ifdef RT_USING_DFS
#include "sd.h"
#endif

#ifdef RT_USING_LWIP
#include "sam7x_emac.h"
extern rt_err_t eth_system_device_init(void);
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>
extern int finsh_system_init(void);
#endif

/**
 * @addtogroup sam7x256
 */

/*@{*/
#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#endif

#ifdef __GNUC__
extern unsigned char __bss_start;
extern unsigned char __bss_end;
#endif

extern void rt_hw_interrupt_init(void);
extern int  rt_application_init(void);
#ifdef RT_USING_DEVICE
extern rt_err_t rt_hw_serial_init(void);
#endif
#ifdef RT_USING_FINSH
extern int finsh_system_init(void);
#endif

void led_flash()
{
    int i;
    static int j = 0;

    rt_hw_board_led_off(j);
    for (i = 0; i < 2000000; i ++);

    j ++;
    if (j >= 4) j = 0;

    rt_hw_board_led_on(j);
    for (i = 0; i < 2000000; i ++);
}

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* init hardware interrupt */
    rt_hw_interrupt_init();

    /* init board */
    rt_hw_board_init();

    rt_show_version();

    /* init timer system */
    rt_system_timer_init();

#ifdef RT_USING_HEAP
#ifdef __CC_ARM
    rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)0x00210000);
#elif __ICCARM__
    rt_system_heap_init(__segment_end("HEAP"), (void*)0x00210000);
#else
    rt_system_heap_init(&__bss_end, (void*)0x00210000);
#endif
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

#ifdef RT_USING_HOOK /* if the hook is used */
    /* set idle thread hook */
    rt_thread_idle_sethook(led_flash);
#endif

#ifdef RT_USING_DEVICE
    /* init hardware serial device */
    rt_hw_serial_init();

#ifdef RT_USING_DFS
    rt_hw_sdcard_init();
#endif
#endif

    /* init application */
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
    finsh_set_device("uart1");
#endif

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

#ifdef __CC_ARM
int main (void)
{
    /* invoke rtthread_startup */
    rtthread_startup();

    return 0;
}
#endif

/*@}*/
