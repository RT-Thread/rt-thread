/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-27     SummerGift   add spi flash port file
 */

#include <rtthread.h>
#include "fal.h"

#if defined(BSP_USING_ON_CHIP_FLASH)
static int rt_hw_on_chip_flash_init(void)
{
    fal_init();
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_on_chip_flash_init);
#endif

