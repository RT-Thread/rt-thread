/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          rewrite
 */

#ifndef __DRV_WDT_H__
#define __DRV_WDT_H__

#include "board.h"

struct swm_wdt_cfg
{
    const char *name;
    WDT_TypeDef *WDTx;
};

struct swm_wdt
{
    struct swm_wdt_cfg *cfg;
    struct rt_watchdog_device wdt_device;
};

int rt_hw_wdt_init(void);

#endif /* __DRV_WDT_H__ */
