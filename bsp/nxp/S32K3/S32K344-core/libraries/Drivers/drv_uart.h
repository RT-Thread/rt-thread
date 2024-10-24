/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-19     Pillar       first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_SERIAL
#include "rtdevice.h"
#include <rthw.h>

int rt_hw_usart_init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif  /* __DRV_USART_H__ */
