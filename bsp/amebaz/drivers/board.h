/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
