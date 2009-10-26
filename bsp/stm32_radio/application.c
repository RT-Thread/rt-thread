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
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <rtthread.h>
#include <finsh.h>

#include <stm32f10x.h>
#include "board.h"
#include "netbuffer.h"
#include "lcd.h"

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:FAT filesystem init */
#include <dfs_fat.h>
/* dfs filesystem:EFS filesystem init */
#include <dfs_efs.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#endif

/*
key_enter   PA0
key_down    PA1
key_up      PA2
key_right   PC2
key_left    PC3
*/
#define key_enter_GETVALUE()  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define key_down_GETVALUE()   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define key_up_GETVALUE()     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define key_right_GETVALUE()  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)
#define key_left_GETVALUE()   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)

void rt_key_entry(void *parameter)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    while (1)
    {
        if ( key_enter_GETVALUE() == 0 )rt_kprintf("key_enter\r\n");
        if ( key_down_GETVALUE()  == 0 )rt_kprintf("key_down\r\n");
        if ( key_up_GETVALUE()    == 0 )rt_kprintf("key_up\r\n");
        if ( key_right_GETVALUE() == 0 )rt_kprintf("key_right\r\n");
        if ( key_left_GETVALUE()  == 0 )rt_kprintf("key_left\r\n");
        rt_thread_delay(20);
    }
}

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
    /* Filesystem Initialization */
#ifdef RT_USING_DFS
    {
        /* init the device filesystem */
        dfs_init();
#ifdef RT_USING_DFS_EFSL
        /* init the efsl filesystam*/
        efsl_init();

        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "efs", 0, 0) == 0)
            rt_kprintf("File System initialized!\n");
        else
            rt_kprintf("File System init failed!\n");
#elif defined(RT_USING_DFS_ELMFAT)
        /* init the elm FAT filesystam*/
        elm_init();

        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
            rt_kprintf("File System initialized!\n");
        else
            rt_kprintf("File System init failed!\n");
#endif
    }
#endif

    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif

#if STM32_EXT_SRAM
	/* init netbuf worker */
	net_buf_init(320 * 1024);
#endif

	/* RTGUI Initialization */
#ifdef RT_USING_RTGUI
	{
		rtgui_rect_t rect;

		rtgui_system_server_init();

		/* register dock panel */
		rect.x1 = 0;
		rect.y1 = 0;
		rect.x2 = 240;
		rect.y2 = 25;

		rtgui_panel_register("info", &rect);

		/* register main panel */
		rect.x1 = 0;
		rect.y1 = 25;
		rect.x2 = 240;
		rect.y2 = 320;
		rtgui_panel_register("main", &rect);

		rt_hw_lcd_init();
	}
#endif
}

int rt_application_init()
{
    rt_thread_t init_thread;

	rt_hw_lcd_init();

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

    /* create keypad thread */
    {
        rt_thread_t key_tid;
        key_tid = rt_thread_create("key",
                                   rt_key_entry, RT_NULL,
                                   512, 30, 5);
        if (key_tid != RT_NULL) rt_thread_startup(key_tid);
    }
    return 0;
}

/*@}*/
