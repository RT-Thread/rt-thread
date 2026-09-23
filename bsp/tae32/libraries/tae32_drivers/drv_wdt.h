/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-02-22     yeml           the first version
 */

#ifndef __DRV_WDT_H__
#define __DRV_WDT_H__

#include <rtdevice.h>
#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined SOC_SERIES_TAE32G58xx
#include "tae32g58xx_ll_iwdg.h"
#endif

struct tae32_wdt
{
    rt_watchdog_t watchdog;

    IWDG_TypeDef *Instance;
    IWDG_InitTypeDef config;
    rt_uint16_t is_start;
};


#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

