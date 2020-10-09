/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-07-27     thread-liu        first version
 */

#include "board.h"
//#define DRV_DEBUG
#define LOG_TAG             "drv.rcc"
#include <drv_log.h>
#include <string.h>
#include <stdlib.h>

static void enable_clock(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
}

static void disable_clock(void)
{
    __HAL_RCC_GPIOD_CLK_DISABLE();
}

static int rcc_sample(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (!strcmp(argv[1], "enable"))
        { 
           enable_clock();
           return RT_EOK;
        }
        else if (!strcmp(argv[1], "disable"))
        {
            disable_clock();
            return RT_EOK;
        }
        else
        {
            goto _exit;
        }
    }
_exit:
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("rcc_sample enable        - enable GPIOD clock, the LD8 will blink '\n");
        rt_kprintf("rcc_sample disable       - disable GPIOD clock, the LD8 will stop blink'\n");
    }

    return -RT_ERROR;
}
MSH_CMD_EXPORT(rcc_sample, rcc use sample);
