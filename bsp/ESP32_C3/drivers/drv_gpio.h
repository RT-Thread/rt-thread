/*
 * Copyright (c) 2021-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-03     supperthomas first version
 *
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtconfig.h>

#ifdef RT_USING_PIN
int rt_hw_pin_init(void);
#endif

#endif /* __DRV_GPIO_H__ */