/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rthw.h>
#include <rtdevice.h>
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define __HT32_PORT(port)  HT_GPIO##port##_BASE

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__HT32_PORT(PORTx) - (rt_base_t)HT_GPIOA_BASE)/(0x2000UL) )) + PIN)

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */
