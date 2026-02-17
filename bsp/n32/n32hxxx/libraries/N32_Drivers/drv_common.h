/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include <rthw.h>
#include <board.h>
#include <rtthread.h>
#ifdef RT_USING_DEVICE
    #include <rtdevice.h>
#endif /* RT_USING_DEVICE */

#ifdef __cplusplus
extern "C" {
#endif

void _Error_Handler(char *s, int num);

#ifndef Error_Handler
#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#endif

#ifdef __cplusplus
}
#endif

#endif
