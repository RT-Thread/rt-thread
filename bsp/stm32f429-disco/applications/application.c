/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup. 
 */

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#include "stm32f4xx_eth.h"
#endif

#ifdef RT_USING_GDB
#include <gdb_stub.h>
#endif

#include "drv_touch.h"

#ifdef PKG_USING_LITTLEVGL2RTT
#include "littlevgl2rtt.h"
#endif 

static void rt_touch_thread_entry(void *parameter)
{
    int16_t x;
    int16_t y;
    struct touch_state ts;
    while(1)
    {
        touch_get_state(&ts);

#ifdef PKG_USING_LITTLEVGL2RTT    
        if(ts.pressed) 
        {
            x = (3706 - ts.x) / 14;
            y = (-461 + ts.y) / 10.5;
        
            littlevgl2rtt_send_input_event(x, y, LITTLEVGL2RTT_INPUT_DOWN);
        }
        else
            littlevgl2rtt_send_input_event(-1, -1, LITTLEVGL2RTT_INPUT_UP);
#endif
        rt_thread_mdelay(100);
    }
}

void rt_init_thread_entry(void* parameter)
{
    rt_thread_t tid;
    
    /* GDB STUB */
#ifdef RT_USING_GDB
    gdb_set_device("uart6");
    gdb_start();
#endif

    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);

        /* register ethernetif device */
        eth_system_device_init();

        rt_hw_stm32_eth_init();

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif
    
    rt_components_init();

    rt_device_t tscreen = rt_device_find("touch");
    rt_device_open(tscreen, RT_DEVICE_FLAG_RDWR);

    tid = rt_thread_create("touch",
                           rt_touch_thread_entry, RT_NULL,
                           1024, 4, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);
                                      
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

/*@}*/
