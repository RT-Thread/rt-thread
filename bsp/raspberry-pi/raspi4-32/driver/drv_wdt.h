/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-10-26     bigmagic       first version
 */
#ifndef __DRV_WDT_H__
#define __DRV_WDT_H__

#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"

struct raspi_wdt_driver
{
    rt_uint32_t timeout;
};

int rt_hw_wdt_init(void);

#endif
