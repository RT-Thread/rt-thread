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
 * 2006-10-08     Bernard      add board.h to this bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#define RT_USING_BOARD_SRAM

#define BOARD_SRAM_BEGIN	0x68000000
#define BOARD_SRAM_END		0x68080000

void rt_hw_board_led_on(int n);
void rt_hw_board_led_off(int n);
void rt_hw_board_init(void);

void rt_hw_usart_init(void);
void rt_hw_sdcard_init(void);

#endif
