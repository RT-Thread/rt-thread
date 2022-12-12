/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-7-21      Rbb666       first version
 */

#ifndef __DRV_WDT_H__
#define __DRV_WDT_H__

#include <rtthread.h>
#include "board.h"

struct ifx_wdt_cfg
{
    const char *name;
    cyhal_wdt_t *WDTx;
};

struct ifx_wdt
{
    struct ifx_wdt_cfg *cfg;
    struct rt_watchdog_device wdt_device;
};

int rt_hw_wdt_init(void);

#endif /* __DRV_WDT_H__ */
