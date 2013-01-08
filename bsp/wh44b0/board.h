/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-23     Bernard      first version
 * 2006-09-24     Bernard      add rt_hw_finsh_init declaration
 */

#ifndef __BOARD_H__
#define __BOARD_H__

void rt_hw_board_init(void);
void rt_hw_led_set(rt_uint32_t led);
void rt_hw_led_flash(void);

#ifdef RT_USING_FINSH
void rt_hw_finsh_init(void);
#endif

#endif
