/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-27   Chushicheng    the first version
 */

#ifndef DRV_I2C_H
#define DRV_I2C_H

#include <rtdevice.h>

#ifdef BSP_USING_I2C
int rt_hw_i2c_init(void);
#endif /* BSP_USING_I2C */

#endif  /* DRV_I2C_H */
