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
 *
 */

/**
 * @addtogroup kinetis
 */
/*@{*/

#include <stdio.h>
#include "fsl_debug_console.h"

#include <board.h>
#include <rtthread.h>


#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#include "stm32_eth.h"
#endif

extern long list_thread(void);

void rt_init_thread_entry(void* parameter)
{
    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);

        /* register ethernetif device */
        eth_system_device_init();

        rt_hw_stm32_eth_init();
        /* re-init device driver */
        rt_device_init_all();

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif

//FS

//GUI

}

float f_var1;
float f_var2;
float f_var3;
float f_var4;

ALIGN(RT_ALIGN_SIZE)
static char thread_demo_stack[1024];
static struct rt_thread demo;
static rt_thread_t init_thread;

#if 0
//  FTM pins that used
   /* FTM0_CH6 -- PTD6 -- ELEV B38 */
    PORT_HAL_SetMuxMode(PORTD_BASE_PTR, 6u, kPortMuxAlt4);
    /* FTM0_CH7 -- PTD7 -- ELEV B52 */
    PORT_HAL_SetMuxMode(PORTD_BASE_PTR, 7u, kPortMuxAlt4);
    /* FTM2_CH0 -- PTB18 -- ELEV B66 */
    PORT_HAL_SetMuxMode(PORTB_BASE_PTR, 18u, kPortMuxAlt3);
    /* FTM2_CH1 -- PTB19 -- ELEV B72 */
    PORT_HAL_SetMuxMode(PORTB_BASE_PTR, 19u, kPortMuxAlt3);
#endif


static void rt_thread_entry_demo(void* parameter)
{
    LED1_EN;
    while (1)
    {      
       LED1_TOGGLE;
       rt_thread_delay(RT_TICK_PER_SECOND*5);
    }
}

int rt_application_init()
{
#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 80, 20);
#endif
    

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

    //------- init demo thread
    rt_thread_init(&demo,
                   "demo",
                   rt_thread_entry_demo,
                   RT_NULL,
                   &thread_demo_stack[0],
                   sizeof(thread_demo_stack),11,5);
    rt_thread_startup(&demo);
    return 0;
}

/*@}*/
