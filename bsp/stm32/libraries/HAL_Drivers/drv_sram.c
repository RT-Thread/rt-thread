/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-24     zylx         first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_SRAM
#include <sram_port.h>

#define DRV_DEBUG
#define LOG_TAG             "drv.sram"
#include <drv_log.h>

#ifdef RT_USING_MEMHEAP_AS_HEAP
    static struct rt_memheap system_heap;
#endif

static int SRAM_Init(void)
{
    int result = RT_EOK;

    SRAM_HandleTypeDef hsram = SRAM_CONFIG;
    FSMC_NORSRAM_TimingTypeDef sram_timing  = SRAM_TIMING_CONFIG;
    FSMC_NORSRAM_TimingTypeDef sram_extiming = SRAM_TIMING_CONFIG;

    /* Initialize the SRAM controller */
    if (HAL_SRAM_Init(&hsram, &sram_timing, &sram_extiming) != HAL_OK)
    {
        LOG_E("SRAM init failed!");
        result = -RT_ERROR;
    }
    else
    {
        LOG_D("sram init success, mapped at 0x%X, size is %d bytes, data width is %d", SRAM_BANK_ADDR, SRAM_SIZE, SRAM_DATA_WIDTH);
#ifdef RT_USING_MEMHEAP_AS_HEAP
        /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SRAM is initialized to the heap */
        rt_memheap_init(&system_heap, "sram", (void *)SRAM_BANK_ADDR, SRAM_SIZE);
#endif
    }

    return result;
}
INIT_BOARD_EXPORT(SRAM_Init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
#include "stdlib.h"

int sram_test(uint8_t argc, char **argv)
{
    rt_uint32_t i, address, size;

    if (argc == 1)
    {
        address  = SRAM_BANK_ADDR;
        size = SRAM_SIZE;
    }
    else if (argc == 3)
    {
        address  = atoi(argv[1]);
        size = atoi(argv[2]);
    }
    else
    {
        rt_kprintf("parameter error");
    }

    rt_kprintf("memtest,address: 0x%08X size: 0x%08X\r\n", address, size);

    /**< 8bit test */
    {
        rt_uint8_t *p_uint8_t = (rt_uint8_t *)address;
        for (i = 0; i < size / sizeof(rt_uint8_t); i++)
        {
            *p_uint8_t++ = (rt_uint8_t)i;
        }

        p_uint8_t = (rt_uint8_t *)address;
        for (i = 0; i < size / sizeof(rt_uint8_t); i++)
        {
            if (*p_uint8_t != (rt_uint8_t)i)
            {
                rt_kprintf("8bit test fail @ 0x%08X\r\nsystem halt!!!!!", (rt_uint32_t)p_uint8_t);
                return -RT_ERROR;
            }
            p_uint8_t++;
        }
        rt_kprintf("8bit test pass!!\r\n");
    }

    /**< 16bit test */
    {
        rt_uint16_t *p_uint16_t = (rt_uint16_t *)address;
        for (i = 0; i < size / sizeof(rt_uint16_t); i++)
        {
            *p_uint16_t++ = (rt_uint16_t)i;
        }

        p_uint16_t = (rt_uint16_t *)address;
        for (i = 0; i < size / sizeof(rt_uint16_t); i++)
        {
            if (*p_uint16_t != (rt_uint16_t)i)
            {
                rt_kprintf("16bit test fail @ 0x%08X\r\nsystem halt!!!!!", (rt_uint32_t)p_uint16_t);
                return -RT_ERROR;
            }
            p_uint16_t++;
        }
        rt_kprintf("16bit test pass!!\r\n");
    }

    /**< 32bit test */
    {
        rt_uint32_t *p_uint32_t = (rt_uint32_t *)address;
        for (i = 0; i < size / sizeof(rt_uint32_t); i++)
        {
            *p_uint32_t++ = (rt_uint32_t)i;
        }

        p_uint32_t = (rt_uint32_t *)address;
        for (i = 0; i < size / sizeof(rt_uint32_t); i++)
        {
            if (*p_uint32_t != (rt_uint32_t)i)
            {
                rt_kprintf("32bit test fail @ 0x%08X\r\nsystem halt!!!!!", (rt_uint32_t)p_uint32_t);
                return -RT_ERROR;
            }
            p_uint32_t++;
        }
        rt_kprintf("32bit test pass!!\r\n");
    }

    /**< 32bit Loopback test */
    {
        rt_uint32_t *p_uint32_t = (rt_uint32_t *)address;
        for (i = 0; i < size / sizeof(rt_uint32_t); i++)
        {
            *p_uint32_t  = (rt_uint32_t)p_uint32_t;
            p_uint32_t++;
        }

        p_uint32_t = (rt_uint32_t *)address;
        for (i = 0; i < size / sizeof(rt_uint32_t); i++)
        {
            if (*p_uint32_t != (rt_uint32_t)p_uint32_t)
            {
                rt_kprintf("32bit Loopback test fail @ 0x%08X", (rt_uint32_t)p_uint32_t);
                rt_kprintf(" data:0x%08X \r\n", (rt_uint32_t)*p_uint32_t);
                rt_kprintf("system halt!!!!!", (rt_uint32_t)p_uint32_t);
                return -RT_ERROR;
            }
            p_uint32_t++;
        }
        rt_kprintf("32bit Loopback test pass!!\r\n");
    }
    return RT_EOK;
}
MSH_CMD_EXPORT(sram_test, sram test);
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_SRAM */
