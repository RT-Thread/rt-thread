/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-03-04     Magicoe      for LPC1766 version
 * 2010-05-02     Aozima       add led function
 * 2010-05-24     Bernard      add filesystem initialization and move led function to led.c
 */

/**
 * @addtogroup LPC1700
 */
/*@{*/

#include <rtthread.h>

#include <board.h>

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:ELM FatFs filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{

    /* Filesystem Initialization */
#ifdef RT_USING_DFS
    {
        /* init the device filesystem */
        dfs_init();

        /* init the elm FAT filesystam*/
        elm_init();

        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
            rt_kprintf("File System initialized!\n");
        else
            rt_kprintf("File System init failed!\n");
    }
#endif

    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);
        extern void lpc17xx_emac_hw_init(void);

        eth_system_device_init();

        /* register ethernetif device */
        lpc17xx_emac_hw_init();
        /* init all device */
        rt_device_init_all();

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif
}

// init led
#define rt_hw_led_init()   LPC_GPIO2->DIR |= 1<<25;
// trun on led n
#define rt_hw_led_on(n)    LPC_GPIO2->CLR |= 1<<25;
// trun off led n
#define rt_hw_led_off(n)   LPC_GPIO2->SET |= 1<<25;

ALIGN(RT_ALIGN_SIZE)
static char thread_led_stack[1024];
struct rt_thread thread_led;
static void rt_thread_entry_led(void* parameter)
{
    unsigned int count=0;

    rt_hw_led_init();

    while (1)
    {
        /* led on */
#ifndef RT_USING_FINSH
        rt_kprintf("led on,count : %d\r\n",count);
#endif
        count++;
        rt_hw_led_on(1);
        /* sleep 0.5 second and switch to other thread */
        rt_thread_delay(RT_TICK_PER_SECOND/2);

        /* led off */
#ifndef RT_USING_FINSH
        rt_kprintf("led off\r\n");
#endif
        rt_hw_led_off(1);
        rt_thread_delay(RT_TICK_PER_SECOND/2);
    }
}

int rt_application_init()
{
    rt_thread_t init_thread;

    //------- init led thread
    rt_thread_init(&thread_led,
                   "led",
                   rt_thread_entry_led,
                   RT_NULL,
                   &thread_led_stack[0],
                   sizeof(thread_led_stack),11,5);
    rt_thread_startup(&thread_led);

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 80, 20);
#endif
    if (init_thread != RT_NULL) rt_thread_startup(init_thread);

    return 0;
}

/*@}*/
