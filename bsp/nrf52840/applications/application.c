/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-03-01     Yangfs       the first version
 * 2015-03-27     Bernard      code cleanup.
 */

/**
 * @addtogroup NRF52840
 */
/*@{*/

#include <rtthread.h>
#include "board.h"
#include "rt_nrf_spi.h"

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#endif
}

int rt_application_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 2048,
                            RT_THREAD_PRIORITY_MAX / 3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}


static int rt_hw_w5500_init(void)
{
		rt_hw_spi_device_attach("spi0","spi00");

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_w5500_init);

static void reset(void)
{
		NVIC_SystemReset();
}
MSH_CMD_EXPORT(reset, reset device)

/*@}*/
