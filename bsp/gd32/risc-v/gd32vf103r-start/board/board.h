/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-04     BruceOu      first implementation
 */

#ifndef __BOARD__
#define __BOARD__
#include "gd32vf103.h"
#include "drv_gpio.h"
extern void *_end;
extern void *_heap_end;
#define HEAP_BEGIN  &_end
#define HEAP_END    &_heap_end

void rt_hw_board_init(void);

#endif /* __BOARD__ */

/******************** end of file *******************/
