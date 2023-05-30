/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-02     Aozima       add led function
 */

#include <rtthread.h>

#include <board.h>

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs.h>
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

#ifdef RT_USING_RTGUI
#include <rtgui/driver.h>
#endif

#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
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

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif

#ifdef RT_USING_RTGUI
    {
        extern void rtgui_system_server_init(void);
        extern void application_init(void);

        rt_device_t lcd;

        /* init lcd */
        rt_hw_lcd_init();

        /* find lcd device */
        lcd = rt_device_find("lcd");
        if (lcd != RT_NULL)
        {
            /* set lcd device as rtgui graphic driver */
            rtgui_graphic_set_device(lcd);

            /* init rtgui system server */
            rtgui_system_server_init();

            /* startup rtgui in demo of RT-Thread/GUI examples */
            application_init();
        }
    }
#endif

#ifdef RT_USING_FINSH
    /* initialize finsh */
    finsh_system_init();
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

int rt_application_init(void)
{
    rt_thread_t tid;

    rt_thread_init(&thread_led,
            "led",
            rt_thread_entry_led,
            RT_NULL,
            &thread_led_stack[0],
            sizeof(thread_led_stack),11,5);
    rt_thread_startup(&thread_led);

    tid = rt_thread_create("init",
            rt_init_thread_entry, RT_NULL,
            2048, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}

#if defined(RT_USING_RTGUI) && defined(RT_USING_FINSH)
#include <rtgui/rtgui_server.h>
#include <rtgui/event.h>
#include <rtgui/kbddef.h>

#include <finsh.h>

void key(rt_uint32_t key)
{
    struct rtgui_event_kbd ekbd;

    RTGUI_EVENT_KBD_INIT(&ekbd);
    ekbd.mod  = RTGUI_KMOD_NONE;
    ekbd.unicode = 0;
    ekbd.key = key;

    ekbd.type = RTGUI_KEYDOWN;
    rtgui_server_post_event((struct rtgui_event*)&ekbd, sizeof(ekbd));

    rt_thread_delay(2);

    ekbd.type = RTGUI_KEYUP;
    rtgui_server_post_event((struct rtgui_event*)&ekbd, sizeof(ekbd));
}
FINSH_FUNCTION_EXPORT(key, send a key to gui server);
#endif
