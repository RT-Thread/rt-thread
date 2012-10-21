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
 */

#ifndef __BOARD_H__
#define __BOARD_H__

void rt_hw_board_led_on(int n);
void rt_hw_board_led_off(int n);
void rt_hw_board_init(void);

void rt_hw_serial_init(void);

/* SD Card init function */
void rt_hw_sdcard_init(void);

int rt_hw_mtd_nand_init(void);

int sst25vfxx_mtd_init(const char * nor_name, unsigned int block_start, unsigned int block_end);

void rt_platform_init(void);
#endif
