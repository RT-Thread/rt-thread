/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 * 
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-19     greedyhao         first version
 */

#ifndef DRV_GPIO_H__
#define DRV_GPIO_H__

#include "drv_common.h"
#include "board.h"

#define __AB32_PORT(port)   GPIO##port

int rt_hw_pin_init(void);

#endif // DRV_GPIO_H__
