/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 */

#ifndef __BOARD_H__
#define __BOARD_H__


#define MCK		50000000

void rt_hw_board_led_on(rt_uint32_t);
void rt_hw_board_led_off(rt_uint32_t);
void rt_hw_board_init(void);

#endif
