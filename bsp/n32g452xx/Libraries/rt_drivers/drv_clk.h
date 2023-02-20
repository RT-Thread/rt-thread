/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     breo.com     first version
 */

#ifndef __DRV_CLK_H__
#define __DRV_CLK_H__

#include <stdint.h>
#include <rtthread.h>
#include <rthw.h>
#ifdef RT_USING_DEVICE
    #include <rtdevice.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void DumpClock(const char *msg);
void SetSysClockToHSI(void);
void SetSysClockToHSE(void);

enum
{
    SYSCLK_PLLSRC_HSI,
    SYSCLK_PLLSRC_HSE,
};
void SetSysClockToPLL(uint32_t freq, uint8_t src);

#ifdef __cplusplus
}
#endif

#endif

