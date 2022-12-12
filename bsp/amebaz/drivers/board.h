/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2018-03-15     flyingcys    add amebaz
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef _LITTLE_ENDIAN
#undef _LITTLE_ENDIAN
#endif

#ifdef SECTION
#undef SECTION
#endif

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

void rt_hw_board_init(void);

#endif

//*** <<< end of configuration section >>>    ***
