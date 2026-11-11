/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-14     muaxiaohei   first version
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include <rtthread.h>

#ifdef WCH_USING_FAST_IRQ
#define WCH_IRQ_ATTR __attribute__((interrupt("WCH-Interrupt-fast")))
#else
#define WCH_IRQ_ATTR __attribute__((interrupt()))
#endif

#ifdef __cplusplus
extern "C"
{
#endif

void rt_hw_us_delay(rt_uint32_t us);

#ifdef __cplusplus
}
#endif

#endif
