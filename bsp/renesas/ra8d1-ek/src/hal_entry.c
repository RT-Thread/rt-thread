/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-12-17     Rbb666        first version
 */

#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>

#define DRV_DEBUG
#define LOG_TAG             "main"
#include <drv_log.h>

#define LED_PIN    BSP_IO_PORT_06_PIN_00 /* Onboard LED pins */

void hal_entry(void)
{
    rt_kprintf("\nHello RT-Thread!\n");

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

#ifdef BSP_USING_SDRAM

#ifdef RT_USING_MEMHEAP_AS_HEAP
    struct rt_memheap system_heap;
#endif

#include "ra/board/ra8d1_ek/board_sdram.h"
static int SDRAM_Init(void)
{
    bsp_sdram_init();

    LOG_D("sdram init success, mapped at 0x%X, size is %d bytes, data width is %d", 0x68000000, BSP_USING_SDRAM_SIZE, 16);
#ifdef RT_USING_MEMHEAP_AS_HEAP
    /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SDRAM is initialized to the heap */
    rt_memheap_init(&system_heap, "sdram", (void *)0x68000000, BSP_USING_SDRAM_SIZE);
#endif
    return RT_EOK;
}
INIT_BOARD_EXPORT(SDRAM_Init);
#endif
