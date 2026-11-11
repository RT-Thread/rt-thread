/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-05-13     Jeffery Yuan      first version
 */

#ifndef __DRV_IWDG_H__
#define __DRV_IWDG_H__

#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IWDG1_DEVICE_NAME    "iwdg1"
#define IWDG2_DEVICE_NAME    "iwdg2"

int rt_hw_iwdg1_init(void);
int rt_hw_iwdg2_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_IWDG_H__ */

